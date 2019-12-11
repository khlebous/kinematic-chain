#include "SceneController.h"
#include "..//Utils/ShaderConstants.h"

SceneController::SceneController() :
	camera(std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 1.0f), -90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)))
{
	isCreatingObstacle = false;

	shader = std::make_shared<Shader>("AxesShader.vs", "AxesShader.fs");
	obstacles_shader = std::make_shared<Shader>("ObstaclesShader.vs", "ObstaclesShader.fs");
	robot_shader = std::make_shared<Shader>("RobotShader.vs", "RobotShader.fs");
	texture_shader = std::make_shared<Shader>("TextureShader.vs", "TextureShader.fs");
	points_shader = std::make_shared<Shader>("PointsShader.vs", "PointsShader.fs");


	axes = std::make_shared<Axes>();
	axes->SetShader(shader);

	float arm1_length = 100.f;
	float arm2_length = 80.f;
	Arm start_arm1 = Arm(arm1_length, 0, 0, glm::vec3(0));
	Arm start_arm2 = Arm(arm2_length, 0, 0, glm::vec3(0.2));
	Arm end_arm1 = Arm(arm1_length, 0, 0, glm::vec3(0.2));
	Arm end_arm2 = Arm(arm2_length, 0, 0, glm::vec3(0.4));
	RobotConfiguration start = RobotConfiguration(start_arm1, start_arm2);
	RobotConfiguration end = RobotConfiguration(end_arm1, end_arm2);
	std::shared_ptr<RobotModel> robotModel = std::make_shared<RobotModel>(start, end);
	std::shared_ptr<Robot> robot = std::make_shared<Robot>(robotModel, robot_shader, texture_shader, points_shader);
	simulation = std::make_shared<Simulation>(robot);
	
	std::shared_ptr<ImGuiSimulation> imgui_simulation = std::make_shared<ImGuiSimulation>(simulation);
	imGuiController = std::make_shared<ImGuiController>(imgui_simulation);
}

void SceneController::Update(float deltaTime)
{
	UpdateShaders();

	simulation->Update(deltaTime);
}

void SceneController::Render()
{
	axes->Render();
	simulation->Render();

	glUseProgram(0);
}

void SceneController::RenderImGui()
{
	imGuiController->Render();
}

void SceneController::ProcessObstacle(float xpos, float ypos)
{
	if (!isCreatingObstacle)
	{
		StartCreatingObstacle(xpos, ypos);
		return;
	}

	ContinueCreatingObstacle(xpos, ypos);
}

void SceneController::ProcessFirstConfiguration(float xpos, float ypos)
{
	simulation->GetRobot()->ProcessFirstConfiguration(xpos, ypos);
}

void SceneController::ProcessSecondConfiguration(float xpos, float ypos)
{
	simulation->GetRobot()->ProcessSecondConfiguration(xpos, ypos);
}

void SceneController::OnRightMouseUp()
{
	isCreatingObstacle = false;
}

void SceneController::ProcessWindowResize()
{
	camera->UpdateProjectionMatrix();
	simulation->GetRobot()->ProcessWindowResize();
}

void SceneController::UpdateShaders()
{
	shader->use();
	shader->setMat4(ShaderConstants::VIEW_MTX, camera->View);
	shader->setMat4(ShaderConstants::PROJECTION_MTX, camera->Projection);

	obstacles_shader->use();
	obstacles_shader->setMat4(ShaderConstants::VIEW_MTX, camera->View);
	obstacles_shader->setMat4(ShaderConstants::PROJECTION_MTX, camera->Projection);

	robot_shader->use();
	robot_shader->setMat4(ShaderConstants::VIEW_MTX, camera->View);
	robot_shader->setMat4(ShaderConstants::PROJECTION_MTX, camera->Projection);

	texture_shader->use();
	texture_shader->setMat4(ShaderConstants::VIEW_MTX, camera->View);
	texture_shader->setMat4(ShaderConstants::PROJECTION_MTX, camera->Projection);

	points_shader->use();
	points_shader->setMat4(ShaderConstants::VIEW_MTX, camera->View);
	points_shader->setMat4(ShaderConstants::PROJECTION_MTX, camera->Projection);

	glUseProgram(0);
}

void SceneController::StartCreatingObstacle(float xpos, float ypos)
{
	isCreatingObstacle = true;

	glm::vec2 position = WindowSizeUtils::ParsePos(xpos, ypos);
	glm::vec2 size = glm::vec2(0);
	glm::vec3 color = glm::vec3(
		(float)rand() / RAND_MAX,
		(float)rand() / RAND_MAX,
		(float)rand() / RAND_MAX);

	auto model = std::make_shared<ObstacleModel>(position, size, color);
	simulation->AddObstacle(Obstacle(model, obstacles_shader));
}

void SceneController::ContinueCreatingObstacle(float xpos, float ypos)
{
	glm::vec2 position = WindowSizeUtils::ParsePos(xpos, ypos);
	size_t obstacles_size = simulation->GetObstaclesSize();

	glm::vec2 size = position - simulation->GetObstacle(obstacles_size - 1).GetModel()->GetPosition();
	simulation->GetObstacle(obstacles_size - 1).SetSize(size);
}

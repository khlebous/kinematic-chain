#include "SceneController.h"
#include "..//Utils/ShaderConstants.h"

SceneController::SceneController() :
	camera(std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 1.0f), -90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)))
{
	mode = 0;
	isCreatingObstacle = false;

	shader = std::make_shared<Shader>("AxesShader.vs", "AxesShader.fs");
	obstacles_shader = std::make_shared<Shader>("ObstaclesShader.vs", "ObstaclesShader.fs");
	robot_shader = std::make_shared<Shader>("RobotShader.vs", "RobotShader.fs");
	texture_shader = std::make_shared<Shader>("TextureShader.vs", "TextureShader.fs");

	imGuiController = std::make_shared<ImGuiController>();

	axes = std::make_shared<Axes>();
	axes->SetShader(shader);

	float arm1_length = 100.f;
	float arm2_length = 80.f;
	Arm start_arm1 = Arm(arm1_length, 0, 0, glm::vec3(0));
	Arm start_arm2 = Arm(arm2_length, 0, 0, glm::vec3(0.2));
	Arm end_arm1 = Arm(arm1_length, 0, 0, glm::vec3(0.4));
	Arm end_arm2 = Arm(arm2_length, 0, 0, glm::vec3(0.6));
	RobotConfiguration start = RobotConfiguration(start_arm1, start_arm2);
	RobotConfiguration end = RobotConfiguration(end_arm1, end_arm2);
	std::shared_ptr<RobotModel> robotModel = std::make_shared<RobotModel>(start, end);
	robot = std::make_shared<Robot>(robotModel, robot_shader, texture_shader);
}

void SceneController::Update(float deltaTime)
{
	UpdateShaders();
}

void SceneController::Render()
{
	for (size_t i = 0; i < obstacles.size(); i++)
		obstacles[i].Render();

	axes->Render();
	robot->Render();

	switch (mode)
	{
	case 0: break;
	case 1: break;
	default: break;
	}

	glUseProgram(0);
}

void SceneController::RenderImGui()
{
	imGuiController->Render(obstacles, robot.get());
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
	robot->ProcessFirstConfiguration(xpos, ypos);
}

void SceneController::ProcessSecondConfiguration(float xpos, float ypos)
{
	robot->ProcessSecondConfiguration(xpos, ypos);
}

void SceneController::OnRightMouseUp()
{
	isCreatingObstacle = false;
}

void SceneController::ProcessWindowResize()
{
	camera->UpdateProjectionMatrix();
	robot->ProcessWindowResize();
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
	obstacles.push_back(Obstacle(model, obstacles_shader));
}

void SceneController::ContinueCreatingObstacle(float xpos, float ypos)
{
	glm::vec2 position = WindowSizeUtils::ParsePos(xpos, ypos);
	glm::vec2 size = position - obstacles[obstacles.size() - 1].GetModel()->GetPosition();

	obstacles[obstacles.size() - 1].SetSize(size);
}

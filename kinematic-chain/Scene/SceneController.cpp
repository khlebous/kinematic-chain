#include "SceneController.h"
#include "..//Utils/ShaderConstants.h"

SceneController::SceneController()
{
	mode = 0;
	isCreatingObstacle = false;

	shader = std::make_shared<Shader>("AxesShader.vs", "AxesShader.fs");
	obstacles_shader = std::make_shared<Shader>("ObstaclesShader.vs", "ObstaclesShader.fs");
	robot_shader = std::make_shared<Shader>("RobotShader.vs", "RobotShader.fs");

	imGuiController = std::make_shared<ImGuiController>();
	
	axes = std::make_shared<Axes>();
	axes->SetShader(shader);

	float arm1_length = 0.3f;
	float arm2_length = 0.3f;
	Arm start_arm1 = Arm(arm1_length, 1.5f);
	Arm start_arm2 = Arm(arm2_length, 0.0f);
	Arm end_arm1 = Arm(arm2_length, 0.0f);
	Arm end_arm2 = Arm(arm2_length, 0.0f);
	RobotConfiguration start = RobotConfiguration(start_arm1, start_arm2);
	RobotConfiguration end = RobotConfiguration(end_arm1, end_arm2);
	std::shared_ptr<RobotModel> robotModel = std::make_shared<RobotModel>(start, end);
	robot = std::make_shared<Robot>(robotModel, robot_shader);
}

void SceneController::Render(float deltaTime)
{
	axes->Render();

	for (size_t i = 0; i < obstacles.size(); i++)
		obstacles[i].Render();

	robot->Render();

	switch (mode)
	{
	case 0:
	
		/*glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);*/

		break;
	case 1:
		
		/*glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	default:
		break;
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

void SceneController::EndObstacleEditing()
{
	isCreatingObstacle = false;
}

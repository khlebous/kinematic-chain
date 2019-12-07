#include "SceneController.h"
#include "..//Utils/ShaderConstants.h"

SceneController::SceneController()
{
	mode = 0;
	isCreatingObstacle = false;

	shader = std::make_shared<Shader>("AxesShader.vs", "AxesShader.fs");
	obstacles_shader = std::make_shared<Shader>("ObstaclesShader.vs", "ObstaclesShader.fs");

	imGuiController = std::make_shared<ImGuiController>();
	
	axes = std::make_shared<Axes>();
	axes->SetShader(shader);
}

void SceneController::Render(float deltaTime)
{
	axes->Render();

	for (size_t i = 0; i < obstacles.size(); i++)
		obstacles[i].Render();

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
	imGuiController->Render(obstacles);
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

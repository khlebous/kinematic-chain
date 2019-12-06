#include "SceneController.h"
#include "..//Utils/ShaderConstants.h"

SceneController::SceneController()
{
	mode = 0;

	shader = std::make_shared<Shader>("AxesShader.vs", "AxesShader.fs");

	imGuiController = std::make_shared<ImGuiController>();
	
	axes = std::make_shared<Axes>();
	axes->SetShader(shader);
}

void SceneController::Render(float deltaTime)
{
	axes->Render();

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
	imGuiController->Render();
}

#include "ImGuiController.h"

void ImGuiController::Render(int& mode)
{
	RenderMainMenuBar(mode);

	switch (mode)
	{
	case 0:	break;
	case 1:	break;
	default: break;
	}
}

void ImGuiController::RenderMainMenuBar(int& mode)
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS) | ", 1000.0f / io.Framerate, io.Framerate);

		if (ImGui::BeginMenu("Open"))
		{
			ImGui::RadioButton("Edit mode", &mode, 0);
			ImGui::RadioButton("Path finding", &mode, 1);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

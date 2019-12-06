#include "ImGuiController.h"
#include "..//Utils/WindowConstants.h"

void ImGuiController::Render()
{
	RenderMainMenuBar();

	ImGui::Begin("Inspector", inspectorWindow);

	if (ImGui::BeginTabBar("ModeTabBar", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Edit"))
		{
			RenderEditMode();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("PathFinding"))
		{
			RenderPathFindingMode();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();
}

void ImGuiController::RenderMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS) | ", 1000.0f / io.Framerate, io.Framerate);

		ImGui::EndMainMenuBar();
	}
}

void ImGuiController::RenderEditMode()
{
	ImGui::Text("Edit mode");
}

void ImGuiController::RenderPathFindingMode()
{
	ImGui::Text("Path finding mode");
}

#include "ImGuiController.h"
#include "..//ImGui/imgui.h"

void ImGuiController::Render()
{
	RenderMainMenuBar();

	ImGui::Begin("Inspector", inspectorWindow);

	if (ImGui::BeginTabBar("ModeTabBar", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Edit"))
		{
			imgui_simulation->RenderEditMode();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("PathFinding"))
		{
			imgui_simulation->RenderPathFindingMode();
			imgui_simulation->Render();
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

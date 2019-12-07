#include "ImGuiController.h"
#include "..//Utils/WindowConstants.h"

void ImGuiController::Render(std::vector<Obstacle>& obstacles)
{
	RenderMainMenuBar();

	ImGui::Begin("Inspector", inspectorWindow);

	if (ImGui::BeginTabBar("ModeTabBar", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Edit"))
		{
			RenderEditMode(obstacles);
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

void ImGuiController::RenderEditMode(std::vector<Obstacle>& obstacles)
{
	ImGui::Text("Obstacles");
	size_t obstacle_idx_to_delete = -1;
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		if (ImGui::TreeNode(("obstacle" + std::to_string(i)).c_str()))
		{
			ObstacleModel* model = obstacles[i].GetModel();
			ImGui::SliderFloat2(("position" + std::to_string(i)).c_str(), &model->GetPositionRef()[0], -1.0f, 1.0f);
			ImGui::SliderFloat2(("size" + std::to_string(i)).c_str(), &model->GetSizeRef()[0], -2.0f, 2.0f);
			ImGui::ColorEdit3(("color" + std::to_string(i)).c_str(), &model->GetColorRef()[0]);
			if (ImGui::Button(("delete obstacle" +std::to_string(i)).c_str()))
				obstacle_idx_to_delete = i;
			ImGui::TreePop();
		}
	}

	if (obstacle_idx_to_delete != -1)
	{
		obstacles.erase(obstacles.begin() + obstacle_idx_to_delete);
	}
}

void ImGuiController::RenderPathFindingMode()
{
	ImGui::Text("Path finding mode");
}

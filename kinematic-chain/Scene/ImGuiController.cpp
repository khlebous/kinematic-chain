#include "ImGuiController.h"
#include "..//Utils/WindowConstants.h"
#include "..//ImGui/imgui_internal.h"

void ImGuiController::Render(std::vector<Obstacle>& obstacles, Robot* robot)
{
	RenderMainMenuBar();

	ImGui::Begin("Inspector", inspectorWindow);

	if (ImGui::BeginTabBar("ModeTabBar", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Edit"))
		{
			RenderEditMode(obstacles, robot);
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

void ImGuiController::RenderEditMode(std::vector<Obstacle>& obstacles, Robot* robot)
{
	ImGui::Text("Robot");
	ImGui::Spacing();

	RobotConfiguration& start = robot->GetModel()->GetStartRef();
	RobotConfiguration& end = robot->GetModel()->GetEndRef();
	Arm& arm1 = start.GetArm1Ref();
	Arm& arm2 = start.GetArm2Ref();
	Arm& arm3 = end.GetArm1Ref();
	Arm& arm4 = end.GetArm2Ref();

	if (ImGui::DragFloat("arm1 length", &arm1.GetLengthRef()))
		arm3.SetLength(arm1.GetLength());
	if (ImGui::DragFloat("arm2 length", &arm2.GetLengthRef()))
		arm4.SetLength(arm2.GetLength());

	ImGui::Spacing();
	ImGui::Text("Start configuration");
	PushDisabled();
	ImGui::SliderAngle("arm1 angle", &start.GetArm1AngleRef());
	PopDisabled();
	ImGui::ColorEdit3("arm1 color", &arm1.GetColorRef()[0]);
	ImGui::Spacing();
	PushDisabled();
	ImGui::SliderAngle("arm2 angle", &start.GetArm2AngleRef());
	PopDisabled();
	ImGui::ColorEdit3("arm2 color", &arm2.GetColorRef()[0]);
	ImGui::Checkbox("althernative start configuration", &robot->GetModel()->GetStartRef().GetIsAlthernativeRef());

	ImGui::Spacing();
	ImGui::Text("End configuration");
	PushDisabled();
	ImGui::SliderAngle("arm3 angle", &end.GetArm1AngleRef());
	PopDisabled();
	ImGui::ColorEdit3("arm3 color", &arm3.GetColorRef()[0]);
	ImGui::Spacing();
	PushDisabled();
	ImGui::SliderAngle("arm4 angle", &end.GetArm2AngleRef());
	PopDisabled();
	ImGui::ColorEdit3("arm4 color", &arm4.GetColorRef()[0]);
	ImGui::Checkbox("althernative end configuration", &robot->GetModel()->GetEndRef().GetIsAlthernativeRef());

	ImGui::Separator();

	if (ImGui::Button("Update scene"))
	{
		robot->UpdateParametrization(obstacles);
	}

	ImGui::Separator();

	ImGui::Text("Obstacles");
	size_t obstacle_idx_to_delete = -1;
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		if (ImGui::TreeNode(("obstacle" + std::to_string(i)).c_str()))
		{
			ObstacleModel* model = obstacles[i].GetModel();
			ImGui::DragFloat2(("position" + std::to_string(i)).c_str(), &model->GetPositionRef()[0]);
			ImGui::DragFloat2(("size" + std::to_string(i)).c_str(), &model->GetSizeRef()[0]);
			ImGui::ColorEdit3(("color" + std::to_string(i)).c_str(), &model->GetColorRef()[0]);
			if (ImGui::Button(("delete obstacle" + std::to_string(i)).c_str()))
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

void ImGuiController::PushDisabled()
{
	ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
}

void ImGuiController::PopDisabled()
{
	ImGui::PopItemFlag();
	ImGui::PopStyleVar();
}

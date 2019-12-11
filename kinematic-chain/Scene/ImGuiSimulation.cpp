#include "..//ImGui/imgui.h"
#include "..//Utils/ImGuiUtils.h"
#include "ImGuiSimulation.h"

void ImGuiSimulation::StartSimulationButton(bool disabled)
{
	if (disabled)
		ImGuiUtils::PushDisabledWithAlpha();

	if (ImGui::Button("Start"))
		simulation->StartSimulation();

	if (disabled)
		ImGuiUtils::PopDisabled();
}

void ImGuiSimulation::PauseSimulationButton(bool disabled)
{
	if (disabled)
		ImGuiUtils::PushDisabledWithAlpha();

	if (ImGui::Button("Pause"))
		simulation->PauseSimulation();

	if (disabled)
		ImGuiUtils::PopDisabled();
}

void ImGuiSimulation::StopSimulationButton(bool disabled)
{
	if (disabled)
		ImGuiUtils::PushDisabledWithAlpha();

	if (ImGui::Button("Stop"))
		simulation->StopSimulation();

	if (disabled)
		ImGuiUtils::PopDisabled();
}

void ImGuiSimulation::SimulationParametres()
{
	ImGui::Text("Is simulating: "); ImGui::SameLine();
	ImGui::Text(simulation->isSimulating ? "true" : "false");

	if (simulation->isSimulating)
	{
		ImGui::SameLine();
		ImGui::Text("   Is paused: "); ImGui::SameLine();
		ImGui::Text(simulation->isPaused ? "true" : "false");
	}

	ImGui::Text("Time %.1f", simulation->current_time);

	bool startButtonDisabled = simulation->isSimulating && !simulation->isPaused;
	StartSimulationButton(startButtonDisabled);

	ImGui::SameLine();

	bool pauseButtonDisabled = !simulation->isSimulating || simulation->isPaused;
	PauseSimulationButton(pauseButtonDisabled);

	ImGui::SameLine();

	bool stopButtonDisabled = !simulation->isSimulating;
	StopSimulationButton(stopButtonDisabled);

	ImGui::DragFloat("delta", &simulation->simulation_time, 0.001f);
	ImGui::SliderFloat("simulation_speed", &simulation->simulation_speed, 1.0f, 10.0f);
}

void ImGuiSimulation::Render()
{
	SimulationParametres();
	ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
}

void ImGuiSimulation::RenderEditMode()
{
	ImGui::Text("Robot");
	ImGui::Spacing();

	RobotModel* robot_model = simulation->GetRobot()->GetModel();

	RobotConfiguration& start = robot_model->GetStartRef();
	RobotConfiguration& end = robot_model->GetEndRef();
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
	ImGuiUtils::PushDisabledWithAlpha();
	ImGui::SliderAngle("arm1 angle", &start.GetArm1AngleRef());
	ImGuiUtils::PopDisabled();
	ImGui::ColorEdit3("arm1 color", &arm1.GetColorRef()[0]);
	ImGui::Spacing();
	ImGuiUtils::PushDisabledWithAlpha();
	ImGui::SliderAngle("arm2 angle", &start.GetArm2AngleRef());
	ImGuiUtils::PopDisabled();
	ImGui::ColorEdit3("arm2 color", &arm2.GetColorRef()[0]);
	ImGui::Checkbox("althernative start configuration", &robot_model->GetStartRef().GetIsAlthernativeRef());

	ImGui::Spacing();
	ImGui::Text("End configuration");
	ImGuiUtils::PushDisabledWithAlpha();
	ImGui::SliderAngle("arm3 angle", &end.GetArm1AngleRef());
	ImGuiUtils::PopDisabled();
	ImGui::ColorEdit3("arm3 color", &arm3.GetColorRef()[0]);
	ImGui::Spacing();
	ImGuiUtils::PushDisabledWithAlpha();
	ImGui::SliderAngle("arm4 angle", &end.GetArm2AngleRef());
	ImGuiUtils::PopDisabled();
	ImGui::ColorEdit3("arm4 color", &arm4.GetColorRef()[0]);
	ImGui::Checkbox("althernative end configuration", &robot_model->GetEndRef().GetIsAlthernativeRef());

	ImGui::Separator();

	ImGui::Text("Obstacles");
	size_t obstacle_idx_to_delete = -1;
	bool obstacle_changed = false;

	for (size_t i = 0; i < simulation->GetObstaclesSize(); i++)
	{
		if (ImGui::TreeNode(("obstacle" + std::to_string(i)).c_str()))
		{
			ObstacleModel* model = simulation->GetObstacle(i).GetModel();
			if (ImGui::DragFloat2(("position" + std::to_string(i)).c_str(), &model->GetPositionRef()[0]))
				obstacle_changed = true;
			
			if (ImGui::DragFloat2(("size" + std::to_string(i)).c_str(), &model->GetSizeRef()[0]))
				obstacle_changed = true;

			if(ImGui::ColorEdit3(("color" + std::to_string(i)).c_str(), &model->GetColorRef()[0]))
				obstacle_changed = true;

			if (ImGui::Button(("delete obstacle" + std::to_string(i)).c_str()))
				obstacle_idx_to_delete = i;
			ImGui::TreePop();
		}
	}

	if (obstacle_idx_to_delete != -1)
	{
		simulation->DeleteObstacle(obstacle_idx_to_delete);
		obstacle_changed = true;
	}
}

void ImGuiSimulation::RenderPathFindingMode()
{
	ImGui::Text("Path finding mode");

	if (ImGui::Button("Update configuration space"))
	{
		simulation->UpdateParametrization();
	}

	ImGui::Separator();

	if (ImGui::Button("Flood fill"))
	{
		simulation->DoFloodFill();
	}
}

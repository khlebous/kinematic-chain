#pragma once

#include <memory>
#include <vector>
#include "..//ImGui/imgui.h"
#include "Obstacle.h"
#include "Robot.h"

class ImGuiController
{
	bool* inspectorWindow = NULL;

public:
	ImGuiController() { }
	~ImGuiController() { }

	void Render(std::vector<Obstacle>& obstacles, Robot* robot);

private:
	void RenderMainMenuBar();
	void RenderEditMode(std::vector<Obstacle>& obstacles, Robot* robot);
	void RenderPathFindingMode();

	void PushDisabled();
	void PopDisabled();
};

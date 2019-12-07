#pragma once

#include <memory>
#include <vector>
#include "..//ImGui/imgui.h"
#include "Obstacle.h"

class ImGuiController
{
	bool* inspectorWindow = NULL;

public:
	ImGuiController() { }
	~ImGuiController() { }

	void Render(std::vector<Obstacle>& obstacles);

private:
	void RenderMainMenuBar();
	void RenderEditMode(std::vector<Obstacle>& obstacles);
	void RenderPathFindingMode();
};

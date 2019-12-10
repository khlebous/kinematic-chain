#pragma once
#include <memory>
#include "ImGuiSimulation.h"

class ImGuiController
{
	std::shared_ptr<ImGuiSimulation> imgui_simulation;
	bool* inspectorWindow = NULL;

public:
	ImGuiController(std::shared_ptr<ImGuiSimulation> _s) { imgui_simulation = _s; }
	~ImGuiController() { }

	void Render();

private:
	void RenderMainMenuBar();
};

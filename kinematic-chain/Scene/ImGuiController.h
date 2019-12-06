#pragma once

#include <memory>
#include "..//ImGui/imgui.h"

class ImGuiController
{
	bool* inspectorWindow = NULL;

public:
	ImGuiController() { }
	~ImGuiController() { }

	void Render();

private:
	void RenderMainMenuBar();
	void RenderEditMode();
	void RenderPathFindingMode();
};

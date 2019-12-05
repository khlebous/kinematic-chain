#pragma once

#include <memory>
#include "..//ImGui/imgui.h"

class ImGuiController
{
public:
	ImGuiController() {	}
	~ImGuiController() {	}

	void Render(int& activeSimulation);

private:
	void RenderMainMenuBar(int& activeSimulation);
};

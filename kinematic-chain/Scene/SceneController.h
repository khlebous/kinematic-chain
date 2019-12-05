#pragma once
#include <memory>
#include "ImGuiController.h"
#include "Axes.h"

class SceneController
{
	std::shared_ptr<Shader> shader;

	std::shared_ptr<Axes> axes;
	std::shared_ptr<ImGuiController> imGuiController;

	int mode;

public:
	SceneController();

	void Render(float deltaTime);
	void RenderImGui();

private:
};

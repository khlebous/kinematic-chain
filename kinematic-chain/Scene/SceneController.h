#pragma once
#include <memory>
#include "ImGuiController.h"
#include "Axes.h"
#include "Obstacle.h"
#include "Robot.h"
#include "..//Utils/WindowSizeUtils.h"
#include "Camera.h"
#include "Simulation.h"

class SceneController
{
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Shader> obstacles_shader;
	std::shared_ptr<Shader> robot_shader;
	std::shared_ptr<Shader> texture_shader;
	std::shared_ptr<Shader> points_shader;

	std::shared_ptr<Axes> axes;
	std::shared_ptr<ImGuiController> imGuiController;
	std::shared_ptr<Camera> camera;

	std::shared_ptr<Simulation> simulation;

	bool isCreatingObstacle;

public:
	SceneController();

	void Update(float deltaTime);
	void Render();
	void RenderImGui();
	void ProcessObstacle(float xpos, float ypos);
	void ProcessFirstConfiguration(float xpos, float ypos);
	void ProcessSecondConfiguration(float xpos, float ypos);
	void ProcessAlternativeFirstConfiguration() { simulation->GetRobot()->ProcessAlternativeFirstConfiguration(); }
	void ProcessAlternativeSecondConfiguration() { simulation->GetRobot()->ProcessAlternativeSecondConfiguration(); }
	void UpdateConfigurationSpace() { simulation->UpdateParametrization(); }
	void DoFloodFill() { simulation->DoFloodFill(); }
	void OnRightMouseUp();
	void ProcessWindowResize();

private:
	void UpdateShaders();
	void StartCreatingObstacle(float xpos, float ypos);
	void ContinueCreatingObstacle(float xpos, float ypos);
};

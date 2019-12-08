#pragma once
#include <memory>
#include "ImGuiController.h"
#include "Axes.h"
#include "Obstacle.h"
#include "Robot.h"
#include "..//Utils/WindowSizeUtils.h"
#include "Camera.h"

class SceneController
{
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Shader> obstacles_shader;
	std::shared_ptr<Shader> robot_shader;
	std::shared_ptr<Shader> texture_shader;

	std::shared_ptr<Axes> axes;
	std::shared_ptr<ImGuiController> imGuiController;
	std::shared_ptr<Camera> camera;

	std::vector<Obstacle> obstacles;
	std::shared_ptr<Robot> robot;

	int mode;
	bool isCreatingObstacle;

public:
	SceneController();

	void Update(float deltaTime);
	void Render();
	void RenderImGui();
	void ProcessObstacle(float xpos, float ypos);
	void ProcessFirstConfiguration(float xpos, float ypos);
	void OnRightMouseUp();
	void ProcessWindowResize();

private:
	void UpdateShaders();
	void StartCreatingObstacle(float xpos, float ypos);
	void ContinueCreatingObstacle(float xpos, float ypos);
};

#pragma once
#include <memory>
#include "ImGuiController.h"
#include "Axes.h"
#include "Obstacle.h"
#include "Robot.h"
#include "..//Utils/WindowSizeUtils.h"

class SceneController
{
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Shader> obstacles_shader;
	std::shared_ptr<Shader> robot_shader;

	std::shared_ptr<Axes> axes;
	std::shared_ptr<ImGuiController> imGuiController;

	std::vector<Obstacle> obstacles;
	std::shared_ptr<Robot> robot;

	int mode;
	bool isCreatingObstacle;

public:
	SceneController();

	void Render(float deltaTime);
	void RenderImGui();
	void ProcessObstacle(float xpos, float ypos);
	void EndObstacleEditing();

private:
	void StartCreatingObstacle(float xpos, float ypos)
	{
		isCreatingObstacle = true;

		glm::vec2 position = WindowSizeUtils::ParsePos(xpos, ypos);
		glm::vec2 size = glm::vec2(0);
		glm::vec3 color = glm::vec3(
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX,
			(float)rand() / RAND_MAX);

		auto model = std::make_shared<ObstacleModel>(position, size, color);
		obstacles.push_back(Obstacle(model, obstacles_shader));
		std::cout << "push_back" << std::endl;
	}

	void ContinueCreatingObstacle(float xpos, float ypos)
	{
		glm::vec2 position = WindowSizeUtils::ParsePos(xpos, ypos);
		glm::vec2 size = position - obstacles[obstacles.size() - 1].GetModel()->GetPosition();
		
		obstacles[obstacles.size() - 1].SetSize(size);
	}
};

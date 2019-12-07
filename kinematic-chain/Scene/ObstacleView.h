#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "Shader.h"
#include "ObstacleModel.h"

// TODO one obstacle view for all obstacles
class ObstacleView
{
	unsigned int VBO, VAO, EBO;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<ObstacleModel> model;

public:
	ObstacleView(std::shared_ptr<ObstacleModel> _m, std::shared_ptr<Shader> _s);

	const std::shared_ptr<Shader> GetShader() { return shader; };

	void Render();
};

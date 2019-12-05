#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

#include "Shader.h"
#include "../Utils/ColorConstants.h"

class Axes
{
	unsigned int VAO, VBO, EBO;
	std::shared_ptr<Shader> shader;
	glm::mat4 model;

	const int indices_size = 4;

public:
	Axes();
	~Axes();

	void SetShader(std::shared_ptr<Shader> _s) { shader = _s; }

	void Render();

private:
	void GenerateBuffors();
};

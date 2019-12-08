#pragma once
#include "Shader.h"
#include "RobotModel.h"

class RobotView
{
	unsigned int VBO, VAO, EBO;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<RobotModel> model;

public:
	RobotView(std::shared_ptr<RobotModel> _m, std::shared_ptr<Shader> _s);

	const std::shared_ptr<Shader> GetShader() { return shader; };

	void Render();

private:
	void RenderConfiguration(RobotConfiguration& configuration);
};

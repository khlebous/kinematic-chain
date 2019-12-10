#pragma once
#include <memory>
#include "..//Utils/WindowConstants.h"
#include "ConfigurationSpaceModel.h"
#include "RobotModel.h"
#include "Shader.h"
#define N 360

class ConfigurationSpaceView
{
	std::shared_ptr<ConfigurationSpaceModel> model;
	std::shared_ptr<RobotModel> robot_model;
	std::shared_ptr<Shader> texture_shader;
	std::shared_ptr<Shader> points_shader;

	unsigned int texture1;
	unsigned int VBO, VAO, EBO;
	unsigned int rVBO, rVAO;

public:
	ConfigurationSpaceView(std::shared_ptr<ConfigurationSpaceModel> _m,
		std::shared_ptr<Shader> _ts, std::shared_ptr<RobotModel> _rm, std::shared_ptr<Shader> _rs);
	~ConfigurationSpaceView()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glDeleteVertexArrays(1, &rVAO);
		glDeleteBuffers(1, &rVBO);
	}

	void Render(bool isRunning);
	void OnWindowSizeChanged() { UpdateTexture(); }
	void UpdateTextureData();

private:
	// TODO refactor
	void UpdateTexture();
};

#pragma once
#include <memory>
#include "..//Utils/WindowConstants.h"
#include "ConfigurationSpaceModel.h"
#include "Shader.h"
#define N 360

class ConfigurationSpaceView
{
	std::shared_ptr<ConfigurationSpaceModel> model;
	std::shared_ptr<Shader> texture_shader;

	unsigned int texture1;
	unsigned int VBO, VAO, EBO;

public:
	ConfigurationSpaceView(std::shared_ptr<ConfigurationSpaceModel> _m,
		std::shared_ptr<Shader> _ts);

	void Render();
	void OnWindowSizeChanged() { UpdateTexture(); }
	void UpdateTextureData();

private:
	// TODO refactor
	void UpdateTexture();
};

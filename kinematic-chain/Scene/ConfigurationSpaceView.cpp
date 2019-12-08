#include "ConfigurationSpaceView.h"

ConfigurationSpaceView::ConfigurationSpaceView(std::shared_ptr<ConfigurationSpaceModel> _m, 
	std::shared_ptr<Shader> _ts): model(_m)
{
	texture_shader = _ts;
	UpdateTexture();
}

void ConfigurationSpaceView::Render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	texture_shader->use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void ConfigurationSpaceView::UpdateTextureData()
{
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N, N, 0, GL_RGB, GL_FLOAT, model->param);
}

void ConfigurationSpaceView::UpdateTexture()
{
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// TODO GL_UNSIGNED_BYTE instead of GL_FLOAT ?
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N, N, 0, GL_RGB, GL_FLOAT, model->param);
	glGenerateMipmap(GL_TEXTURE_2D);

	float width_half = WindowConstants::WIDTH / 2.0f;
	float height_half = WindowConstants::HEIGHT / 2.0f;
	float vertices[] = {
		// positions          // texture coords
		-width_half + N, -height_half + N,   1.0f, 1.0f, // top right
		-width_half + N, -height_half,       0.0f, 1.0f, // bottom right
		-width_half,     -height_half,       0.0f, 0.0f, // bottom left
		-width_half,     -height_half + N,   1.0f, 0.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

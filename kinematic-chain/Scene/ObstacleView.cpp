#include "ObstacleView.h"

ObstacleView::ObstacleView(std::shared_ptr<ObstacleModel> _m, std::shared_ptr<Shader> _s)
{
	model = _m;
	shader = _s;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	UpdateVerticesView();

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void ObstacleView::UpdateVerticesView()
{
	glm::vec2 position = model->GetPosition();
	glm::vec2 size = model->GetSize();

	float vertices[] = { // positions
		position.x + size.x,  position.y + size.y,
		position.x + size.x,  position.y,
		position.x,           position.y,
		position.x,           position.y + size.y,
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void ObstacleView::Render()
{
	shader->use();
	shader->setVec3(ShaderConstants::COLOR, model->GetColor());

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

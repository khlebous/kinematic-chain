#include "Axes.h"

Axes::Axes()
{
	model = glm::mat4(1);
	GenerateBuffors();
}

Axes::~Axes()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Axes::Render()
{
	shader->use();
	shader->setMat4(ShaderConstants::MODEL_MTX, glm::mat4(1));
	
	glLineWidth(1);

	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, indices_size, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Axes::GenerateBuffors()
{
	float vert_basic[] =
	{
		-1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f, 0.0f,   1.0f, 0.0f, 0.0f,

		0.0f, -1.0f,   0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
	};

	std::vector<int> ind_basic = { 0, 1, 2, 3};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_basic), &vert_basic, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_basic.size() * sizeof(int), &ind_basic[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#include "RobotView.h"
#include <glm/gtc/matrix_transform.hpp>

RobotView::RobotView(std::shared_ptr<RobotModel> _m, std::shared_ptr<Shader> _s)
{
	model = _m;
	shader = _s;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	float vertices[] = { 1.0f,  0.0f };
	int indices[] = { 0, 1 };

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RobotView::Render()
{
	shader->use();

	Arm& arm = model->GetStartRef().GetArm1Ref();

	glm::mat4 s_matrix = glm::scale(glm::mat4(1), glm::vec3(arm.GetLength(), 0, 0));
	glm::mat4 r_matrix = glm::rotate(glm::mat4(1), arm.GetAngle(), { 0, 0, 1 });

	shader->setMat4(ShaderConstants::MODEL_MTX,
		r_matrix * s_matrix
	);
	shader->setVec3(ShaderConstants::COLOR, { 0.5f, 0.2f, 0.3f });

	glLineWidth(5);

	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

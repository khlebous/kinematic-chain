#include "ConfigurationSpaceView.h"
#include "..//Utils/EulerAnglesLimitsUtils.h"

ConfigurationSpaceView::ConfigurationSpaceView(std::shared_ptr<ConfigurationSpaceModel> _m, 
	std::shared_ptr<Shader> _ts, std::shared_ptr<RobotModel> _rm, std::shared_ptr<Shader> _rs): model(_m), robot_model(_rm)
{
	texture_shader = _ts;
	robot_shader = _rs;
	UpdateTexture();

	glGenVertexArrays(1, &rVAO);
	glGenBuffers(1, &rVBO);
}

void ConfigurationSpaceView::Render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	texture_shader->use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	float width_half = WindowConstants::WIDTH / 2.0f;
	float height_half = WindowConstants::HEIGHT / 2.0f;

	size_t start_arm1 = (size_t)EulerAnglesLimitsUtils::GetCorrected(glm::degrees(robot_model->GetStartRef().GetArm1Angle()));
	size_t start_arm2 = (size_t)EulerAnglesLimitsUtils::GetCorrected(glm::degrees(robot_model->GetStartRef().GetArm2Angle()));

	size_t end_arm1 = (size_t)EulerAnglesLimitsUtils::GetCorrected(glm::degrees(robot_model->GetEndRef().GetArm1Angle()));
	size_t end_arm2 = (size_t)EulerAnglesLimitsUtils::GetCorrected(glm::degrees(robot_model->GetEndRef().GetArm2Angle()));

	float vert_to_draw[] = { start_arm1 - width_half, start_arm2 - height_half,
		end_arm1 - width_half, end_arm2 - height_half };

	robot_shader->use();
	robot_shader->setVec3(ShaderConstants::COLOR, { 1,0,0 });
	robot_shader->setFloat(ShaderConstants::POINT_SIZE, 5.0f);


	glBindVertexArray(rVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_to_draw), vert_to_draw, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glDrawArrays(GL_POINTS, 0, 2);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);

}

void ConfigurationSpaceView::UpdateTextureData()
{
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N, N, 0, GL_RGB, GL_FLOAT, model->colors);
}

void ConfigurationSpaceView::UpdateTexture()
{
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// TODO GL_UNSIGNED_BYTE instead of GL_FLOAT ?
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N, N, 0, GL_RGB, GL_FLOAT, model->colors);
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

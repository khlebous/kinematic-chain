#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils/WindowConstants.h"

class Camera
{
	glm::vec3 worldUp;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 front;

public:
	glm::vec3 Position;

	// Euler Angles
	float Yaw;
	float Pitch;

	// Mtxs
	glm::mat4 View;
	glm::mat4 Projection;

	float Near;
	float Far;

	Camera(glm::vec3 _pos, float _yaw, float _pitch, glm::vec3 _worldUp, glm::vec3 _front); 

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
	void UpdateCameraVectors();
};

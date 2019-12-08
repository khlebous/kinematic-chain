#include "Camera.h"

Camera::Camera(glm::vec3 _pos, float _yaw, float _pitch, glm::vec3 _worldUp, glm::vec3 _front) :
	Position(_pos), Yaw(_yaw), Pitch(_pitch), worldUp(_worldUp), front(_front),
	Near(0.1f), Far(2.f)
{
	UpdateCameraVectors();
	UpdateProjectionMatrix();
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	View = glm::lookAt(Position, Position + front, up);
}

void Camera::UpdateProjectionMatrix()
{
	float width_half = (float)WindowConstants::WIDTH / 2.0f;
	float height_half = (float)WindowConstants::HEIGHT / 2.0f;

	Projection = glm::ortho(-width_half, width_half, -height_half, height_half, Near, Far);
}

void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	front = glm::normalize(glm::vec3(
		cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
		sin(glm::radians(Pitch)),
		sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))));
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}

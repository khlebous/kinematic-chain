#pragma once
#include <glm/glm.hpp>
#define N 360

class ConfigurationSpaceModel
{
public:
	glm::vec3 param[N][N];

	ConfigurationSpaceModel();
};

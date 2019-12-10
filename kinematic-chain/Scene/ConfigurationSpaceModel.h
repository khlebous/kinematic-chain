#pragma once
#include <vector>
#include <glm/glm.hpp>
#define N 360

class ConfigurationSpaceModel
{
public:
	int no_data = -1;
	int obstacle = -2;

	glm::vec3 colors[N][N];
	int distance[N][N];
	std::vector<float> path;

	ConfigurationSpaceModel();
};

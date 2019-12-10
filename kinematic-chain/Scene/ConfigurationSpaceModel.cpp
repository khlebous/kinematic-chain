#include "ConfigurationSpaceModel.h"

ConfigurationSpaceModel::ConfigurationSpaceModel()
{
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
		{
			colors[i][j] = glm::vec3(0);
			distance[i][j] = no_data;
		}
}

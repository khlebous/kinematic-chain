#include "ConfigurationSpace.h"

ConfigurationSpace::ConfigurationSpace(std::shared_ptr<ConfigurationSpaceModel> _m, 
	std::shared_ptr<RobotModel> _rm, std::shared_ptr<Shader> _ts) :
	model(_m), robot_model(_rm),
	view(std::make_shared<ConfigurationSpaceView>(model, _ts))
{
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			model->param[i][j] = glm::vec3(0);
}

void ConfigurationSpace::UpdateParametrization(const std::vector<Obstacle>& obstacles)
{
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
		{
			model->param[i][j] = glm::vec3(0);
			for (size_t k = 0; k < obstacles.size(); k++)
				UpdateParametrization(obstacles[k], i, j);
		}

	view->UpdateTextureData();
}

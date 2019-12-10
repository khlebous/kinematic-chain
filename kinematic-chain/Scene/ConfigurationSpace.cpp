#include "ConfigurationSpace.h"
#include <queue>
typedef std::pair<int, int> pair_int;

ConfigurationSpace::ConfigurationSpace(std::shared_ptr<ConfigurationSpaceModel> _m,
	std::shared_ptr<RobotModel> _rm, std::shared_ptr<Shader> _ts, std::shared_ptr<Shader> _rs) :
	model(_m), robot_model(_rm),
	view(std::make_shared<ConfigurationSpaceView>(model, _ts, _rm, _rs)) { }

void ConfigurationSpace::UpdateParametrization(const std::vector<Obstacle>& obstacles)
{
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
		{
			model->colors[i][j] = glm::vec3(0);
			model->distance[i][j] = model->no_data;
			for (size_t k = 0; k < obstacles.size(); k++)
				UpdateParametrization(obstacles[k], i, j);
		}

	view->UpdateTextureData();
}

void ConfigurationSpace::DoFloodFill(size_t start_arm1, size_t start_arm2, size_t end_arm1, size_t end_arm2)
{
	std::queue<pair_int> queue;
	queue.push(pair_int(start_arm1, start_arm2));

	int current_value = 1;

	auto WrapF = [](int value, int precision) { return value < 0 ? value + precision : value % precision; };
	while (!queue.empty())
	{
		pair_int p = queue.front();
		queue.pop();
		int x = p.first;
		int y = p.second;

		if (x < 0 || x >= N || y < 0 || y >= N)
			continue;

		if (x == end_arm1 && y == end_arm2)
			break;

		if (model->distance[x][y] != -1)
			continue;

		model->distance[x][y] = current_value;

		queue.push(pair_int(WrapF(x + 1, N), WrapF(y, N)));
		queue.push(pair_int(WrapF(x - 1, N), WrapF(y, N)));
		queue.push(pair_int(WrapF(x, N), WrapF(y + 1, N)));
		queue.push(pair_int(WrapF(x, N), WrapF(y - 1, N)));

		current_value++;
	}

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			if (model->distance[i][j] == model->obstacle || model->distance[i][j] == model->no_data)
				continue;

			model->colors[i][j] = glm::vec3(1.0 - model->distance[i][j] / (float)current_value);
		}
	}

	view->UpdateTextureData();
}

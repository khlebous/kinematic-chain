#include "ConfigurationSpace.h"
#include <queue>
typedef std::pair<int, int> pair_int;
typedef std::pair<pair_int, int> tuple_int;

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
	std::queue<tuple_int> queue;
	queue.push(tuple_int(pair_int(start_arm1, start_arm2), 0));

	auto WrapF = [](int value, int precision) { return value < 0 ? value + precision : value % precision; };
	while (!queue.empty())
	{
		tuple_int p = queue.front();
		queue.pop();

		int x = p.first.first;
		int y = p.first.second;

		if (x < 0 || x >= N || y < 0 || y >= N)
			continue;

		if (model->distance[x][y] != -1)
			continue;

		model->distance[x][y] = p.second;
		if (x == end_arm1 && y == end_arm2)
		{
			break;
		}

		queue.push(tuple_int(pair_int(WrapF(x + 1, N), WrapF(y, N)), p.second + 1));
		queue.push(tuple_int(pair_int(WrapF(x - 1, N), WrapF(y, N)), p.second + 1));
		queue.push(tuple_int(pair_int(WrapF(x, N), WrapF(y + 1, N)), p.second + 1));
		queue.push(tuple_int(pair_int(WrapF(x, N), WrapF(y - 1, N)), p.second + 1));
	}

	int* start = &model->distance[0][0];
	int value = *std::max_element(start, start + N * N);

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			if (model->distance[i][j] == model->obstacle || model->distance[i][j] == model->no_data)
				continue;

			model->colors[i][j] = glm::vec3(1.0 - model->distance[i][j] / (float)value);
		}
	}

	model->path.clear();
	if (model->distance[end_arm1][end_arm2] != -1)
	{
		
		model->path.push_back(end_arm1);
		model->path.push_back(end_arm2);;

		value = model->distance[end_arm1][end_arm2];
		while (value > 0)
		{
			float last_x = model->path[model->path.size() - 2];
			float last_y = model->path[model->path.size() - 1];

			if (model->distance[WrapF(last_x + 1, N)][WrapF(last_y, N)] == value)
			{
				model->path.push_back(WrapF(last_x + 1, N));
				model->path.push_back(WrapF(last_y, N));
			}
			else if (model->distance[WrapF(last_x - 1, N)][WrapF(last_y, N)] == value)
			{
				model->path.push_back(WrapF(last_x - 1, N));
				model->path.push_back(WrapF(last_y, N));
			}
			else if (model->distance[WrapF(last_x, N)][WrapF(last_y + 1, N)] == value)
			{
				model->path.push_back(WrapF(last_x, N));
				model->path.push_back(WrapF(last_y + 1, N));
			}
			else if (model->distance[WrapF(last_x, N)][WrapF(last_y - 1, N)] == value)
			{
				model->path.push_back(WrapF(last_x, N));
				model->path.push_back(WrapF(last_y - 1, N));
			}

			value--;
		}

	}

	view->UpdateTextureData();
}

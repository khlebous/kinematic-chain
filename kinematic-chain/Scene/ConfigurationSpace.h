#pragma once
#include <limits>
#include <memory>
#include <vector>

#include "Arm.h"
#include "RobotModel.h"
#include "Obstacle.h"

#include "ConfigurationSpaceModel.h"
#include "ConfigurationSpaceView.h"
#include "..//Utils/EulerUtils.h"
#define N 360

class ConfigurationSpace
{
	std::shared_ptr<ConfigurationSpaceModel> model;
	std::shared_ptr<ConfigurationSpaceView> view;

	std::shared_ptr<RobotModel> robot_model;

public:
	ConfigurationSpace(std::shared_ptr<ConfigurationSpaceModel> _m, std::shared_ptr<RobotModel> _rm,
		std::shared_ptr<Shader> _ts, std::shared_ptr<Shader> _rs);

	void UpdateParametrization(const std::vector<Obstacle>& obstacles);
	void Render(bool isRunning) { view->Render(isRunning); }
	void OnWindowSizeChanged() { view->OnWindowSizeChanged(); }

	void DoFloodFill(size_t start_arm1, size_t start_arm2, size_t end_arm1, size_t end_arm2);
	size_t GetPathSize() { return model->path.size() / 2; }
	float GetPathElementX(size_t idx) { return model->path[2 * idx]; }
	float GetPathElementY(size_t idx) { return model->path[2 * idx + 1]; }
	bool IsOcupatedWithObstacle(const glm::vec2& pos)
	{
		size_t x = EulerUtils::GetCorrectedAngle(pos.x);
		size_t y = EulerUtils::GetCorrectedAngle(pos.y);

		return model->distance[x][y] == model->obstacle;
	}

private:
	bool Collides(const std::vector<float>& p, const std::vector<float>& q)
	{
		float u1 = std::numeric_limits<float>::min();
		float u2 = std::numeric_limits<float>::max();

		for (size_t i = 0; i < 4; i++)
		{
			if (p[i] == 0)
			{
				if (q[i] < 0)
					return false;
			}
			else
			{
				float t = q[i] / p[i];
				if (p[i] < 0 && u1 < t)
					u1 = t;
				else if (p[i] > 0 && u2 > t)
					u2 = t;
			}
		}

		if (u1 > u2 || u1 > 1 || u1 < 0)
			return false;

		return true;
	}
	bool Collides1(const Obstacle& obstacle, float arm1_angle)
	{
		Arm& arm = robot_model->GetStartRef().GetArm1Ref();

		float vx = glm::cos(glm::radians(arm1_angle)) * arm.GetLength();
		float vy = glm::sin(glm::radians(arm1_angle)) * arm.GetLength();

		float x = 0; // arm1.GetPosition().x
		float y = 0; // arm1.GetPosition().y

		float p[4] = { -vx, vx, -vy, vy };

		ObstacleModel* om = obstacle.GetModel();

		float left = om->GetPosition().x;
		float bottom = om->GetPosition().y;
		float right = om->GetPosition().x + om->GetSize().x;
		float top = om->GetPosition().y + om->GetSize().y;

		if (left > right)
		{
			float tmp = left;
			left = right;
			right = tmp;
		}

		if (bottom < top)
		{
			float tmp = bottom;
			bottom = top;
			top = tmp;
		}

		float q[4] = { x - left, right - x, y - top, bottom - y };

		float u1 = std::numeric_limits<float>::min();
		float u2 = std::numeric_limits<float>::max();

		for (size_t i = 0; i < 4; i++)
		{
			if (p[i] == 0)
			{
				if (q[i] < 0)
					return false;
			}
			else
			{
				float t = q[i] / p[i];
				if (p[i] < 0 && u1 < t)
					u1 = t;
				else if (p[i] > 0 && u2 > t)
					u2 = t;
			}
		}

		if (u1 > u2 || u1 > 1 || u1 < 0)
			return false;

		return true;
	}
	bool Collides2(const Obstacle& obstacle, float arm1_angle, float arm2_angle)
	{
		Arm& arm1 = robot_model->GetStartRef().GetArm1Ref();
		Arm& arm2 = robot_model->GetStartRef().GetArm1Ref();

		float vx = glm::cos(glm::radians(arm1_angle + arm2_angle)) * arm2.GetLength();
		float vy = glm::sin(glm::radians(arm1_angle + arm2_angle)) * arm2.GetLength();

		float x = glm::cos(glm::radians(arm1_angle)) * arm1.GetLength();
		float y = glm::sin(glm::radians(arm1_angle)) * arm1.GetLength();

		float p[4] = { -vx, vx, -vy, vy };

		ObstacleModel* om = obstacle.GetModel();

		float left = om->GetPosition().x;
		float bottom = om->GetPosition().y;
		float right = om->GetPosition().x + om->GetSize().x;
		float top = om->GetPosition().y + om->GetSize().y;

		if (left > right)
		{
			float tmp = left;
			left = right;
			right = tmp;
		}

		if (bottom < top)
		{
			float tmp = bottom;
			bottom = top;
			top = tmp;
		}

		float q[4] = { x - left, right - x, y - top, bottom - y };

		float u1 = std::numeric_limits<float>::min();
		float u2 = std::numeric_limits<float>::max();

		for (size_t i = 0; i < 4; i++)
		{
			if (p[i] == 0)
			{
				if (q[i] < 0)
					return false;
			}
			else
			{
				float t = q[i] / p[i];
				if (p[i] < 0 && u1 < t)
					u1 = t;
				else if (p[i] > 0 && u2 > t)
					u2 = t;
			}
		}

		if (u1 > u2 || u1 > 1 || u1 < 0)
			return false;

		return true;
	}

	std::vector<float> GetPForArm1(float arm1_angle)
	{
		Arm& arm = robot_model->GetStartRef().GetArm1Ref();

		float vx = glm::cos(glm::radians(arm1_angle)) * arm.GetLength();
		float vy = glm::sin(glm::radians(arm1_angle)) * arm.GetLength();

		return { -vx, vx, -vy, vy };
	}
	std::vector<float> GetPForArm2(float arm1_angle, float arm2_angle)
	{
		Arm& arm2 = robot_model->GetStartRef().GetArm2Ref();

		float vx = glm::cos(glm::radians(arm1_angle + arm2_angle)) * arm2.GetLength();
		float vy = glm::sin(glm::radians(arm1_angle + arm2_angle)) * arm2.GetLength();

		return { -vx, vx, -vy, vy };
	}

	glm::vec2 GetPosForArm1()
	{
		float x = 0; // arm1.GetPosition().x
		float y = 0; // arm1.GetPosition().y

		return glm::vec2(x, y);
	}
	glm::vec2 GetPosForArm2(float arm1_angle)
	{
		Arm& arm1 = robot_model->GetStartRef().GetArm1Ref();

		float x = glm::cos(glm::radians(arm1_angle)) * arm1.GetLength();
		float y = glm::sin(glm::radians(arm1_angle)) * arm1.GetLength();

		return glm::vec2(x, y);
	}

	std::vector<float> GetQ(const Obstacle& obstacle, const glm::vec2& pos)
	{
		ObstacleModel* om = obstacle.GetModel();

		float left = om->GetPosition().x;
		float bottom = om->GetPosition().y;
		float right = om->GetPosition().x + om->GetSize().x;
		float top = om->GetPosition().y + om->GetSize().y;

		if (left > right)
		{
			float tmp = left;
			left = right;
			right = tmp;
		}

		if (bottom < top)
		{
			float tmp = bottom;
			bottom = top;
			top = tmp;
		}

		return { pos.x - left, right - pos.x, pos.y - top, bottom - pos.y };
	}

	void UpdateParametrization(const Obstacle& obstacle, size_t arm1_angle, size_t arm2_angle)
	{
		//if (Collides(GetPForArm1(arm1_angle), GetQ(obstacle, GetPosForArm1())))
		if (Collides1(obstacle, arm1_angle))
		{
			model->colors[arm1_angle][arm2_angle] = obstacle.GetModel()->GetColor();
			model->distance[arm1_angle][arm2_angle] = model->obstacle;
			return;
		}

		//if (Collides(GetPForArm2(arm1_angle, arm2_angle), GetQ(obstacle, GetPosForArm2(arm1_angle))))
		if (Collides2(obstacle, arm1_angle, arm2_angle))
		{
			model->colors[arm1_angle][arm2_angle] = obstacle.GetModel()->GetColor();
			model->distance[arm1_angle][arm2_angle] = model->obstacle;
		}
	}
};

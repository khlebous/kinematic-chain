#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Robot.h"

class Simulation
{
	std::shared_ptr<Robot> robot;
	std::vector<Obstacle> obstacles;

public:
	bool isSimulating;
	bool isPaused;
	float simulation_speed;

	float current_time;
	float simulation_time;

	Simulation(std::shared_ptr<Robot> _r);
	~Simulation() { }

	Robot* GetRobot() { return robot.get(); }
	size_t GetObstaclesSize() { return obstacles.size(); }
	Obstacle& GetObstacle(size_t idx) { return obstacles[idx]; };
	void DeleteObstacle(size_t idx) { obstacles.erase(obstacles.begin() + idx); }
	void AddObstacle(const Obstacle& _o) { obstacles.push_back(_o); }
	void UpdateParametrization();
	void DoFloodFill() { robot->DoFloodFill(); }

	void Update(float delta_time);
	void Render();

	void StartSimulation();
	void PauseSimulation();
	void StopSimulation();
};

#include "Simulation.h"

Simulation::Simulation(std::shared_ptr<Robot> _r)
{
	robot = _r;

	isSimulating = false;
	isPaused = false;

	current_time = 0.0f;
	simulation_time = 3.0f;
	simulation_speed = 1.0f;
}

void Simulation::Update(float delta_time)
{
	if (!isSimulating || isPaused)
		return;

	current_time = glm::min(current_time + simulation_speed * delta_time, simulation_time);

	if (current_time >= simulation_time)
	{
		current_time = simulation_time;
		isSimulating = false;
	}

	robot->UpdateCurrent(current_time / simulation_time);
}

void Simulation::Render()
{
	for (size_t i = 0; i < obstacles.size(); i++)
		obstacles[i].Render();

	robot->Render(isSimulating);
}

void Simulation::StartSimulation()
{
	if (isSimulating && isPaused)
	{
		isPaused = false;
		return;
	}

	current_time = 0.0f;
	isSimulating = true;
	isPaused = false;

	//model->ResetParametres();
}

void Simulation::PauseSimulation()
{
	isPaused = true;
}

void Simulation::StopSimulation()
{
	isPaused = false;
	isSimulating = false;

	//model->ResetParametres();
}

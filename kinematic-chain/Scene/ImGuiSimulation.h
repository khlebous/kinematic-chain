#pragma once
#include <glm/glm.hpp>
#include "Simulation.h"
#include "..//Utils/ImGuiUtils.h"

class ImGuiSimulation
{
	std::shared_ptr<Simulation> simulation;
	bool* inspectorWindow = NULL;

public:
	ImGuiSimulation(std::shared_ptr<Simulation> _s) { simulation = _s; }
	~ImGuiSimulation() { delete inspectorWindow; }

	void StartSimulationButton(bool disabled);
	void PauseSimulationButton(bool disabled);
	void StopSimulationButton(bool disabled);

	void SimulationParametres();

	void Render();
	void RenderEditMode();
	void RenderPathFindingMode();
};
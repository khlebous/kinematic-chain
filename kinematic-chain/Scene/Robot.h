#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "RobotModel.h"
#include "RobotView.h"
#include "Obstacle.h"
#include "ConfigurationSpace.h"

#include "..//Utils/WindowSizeUtils.h"
#include "..//Utils/EulerUtils.h"

class Robot
{
	std::shared_ptr<RobotModel> model;
	std::shared_ptr<RobotView> view;
	std::shared_ptr<ConfigurationSpace> configuration_space;

public:
	Robot(std::shared_ptr<RobotModel> _m, std::shared_ptr<Shader> _s, 
		std::shared_ptr<Shader> _ts, std::shared_ptr<Shader> _ps) :
		model(_m),
		view(std::make_shared<RobotView>(_m, _s)),
		configuration_space(std::make_shared<ConfigurationSpace>(std::make_shared<ConfigurationSpaceModel>(), _m, _ts, _ps)) { }
	Robot(const Robot& o) :
		model(std::make_shared<RobotModel>(o.model)),
		view(std::make_shared<RobotView>(model, o.GetView()->GetShader())) { }
	Robot& operator=(const Robot& o);

	RobotModel* GetModel() const { return model.get(); }
	RobotView* GetView() const { return view.get(); }
	ConfigurationSpace* GetConfigurationSpace() const { return configuration_space.get(); }

	void Render(bool isRunning);
	void UpdateConfigurationSpace(const std::vector<Obstacle>& obstacles) { configuration_space->UpdateParametrization(obstacles); }
	void ProcessWindowResize() { configuration_space->OnWindowSizeChanged(); }
	void ProcessFirstConfiguration(glm::vec2 pos) { ProcessConfiguration(model->GetStartRef(), pos); }
	void ProcessSecondConfiguration(glm::vec2 pos) { ProcessConfiguration(model->GetEndRef(), pos); }
	void ProcessAlternativeFirstConfiguration() { model->GetStartRef().Switch(); }
	void ProcessAlternativeSecondConfiguration() { model->GetEndRef().Switch(); }
	void DoFloodFill();
	void UpdateCurrentConfiguration(float simulation_percentage);
	void CheckRobotConfigurationsCorrect();

private:
	glm::vec4 GetNewParametrizations(float x, float y);
	void ProcessConfiguration(RobotConfiguration& configuration, glm::vec2 pos);
	void CheckRobotConfigurationsCorrect(RobotConfiguration& configuration);
};

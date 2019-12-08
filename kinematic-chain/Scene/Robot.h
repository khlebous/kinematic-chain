#pragma once
#include <memory>
#include <limits>
#include <vector>
#include "RobotModel.h"
#include "RobotView.h"
#include "Obstacle.h"
#include "ConfigurationSpace.h"
#define N 360

class Robot
{
	std::shared_ptr<RobotModel> model;
	std::shared_ptr<RobotView> view;
	std::shared_ptr<ConfigurationSpace> configuration_space;

public:
	Robot(std::shared_ptr<RobotModel> _m, std::shared_ptr<Shader> _s, std::shared_ptr<Shader> _ts) :
		model(_m),
		view(std::make_shared<RobotView>(_m, _s)),
		configuration_space(std::make_shared<ConfigurationSpace>(std::make_shared<ConfigurationSpaceModel>(), _m, _ts)) { }
	Robot(const Robot& o) :
		model(std::make_shared<RobotModel>(o.model)),
		view(std::make_shared<RobotView>(model, o.GetView()->GetShader())) { }
	Robot& operator=(const Robot& o);

	RobotModel* GetModel() const { return model.get(); }
	RobotView* GetView() const { return view.get(); }

	void Render();
	void UpdateParametrization(const std::vector<Obstacle>& obstacles) { configuration_space->UpdateParametrization(obstacles); }
	void ProcessWindowResize() { configuration_space->OnWindowSizeChanged(); }
};

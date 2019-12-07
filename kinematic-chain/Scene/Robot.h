#pragma once
#include <memory>
#include "RobotModel.h"
#include "RobotView.h"

class Robot
{
	std::shared_ptr<RobotModel> model;
	std::shared_ptr<RobotView> view;

public:
	Robot(std::shared_ptr<RobotModel> _m, std::shared_ptr<Shader> _s) :
		model(_m), view(std::make_shared<RobotView>( _m, _s)) { }
	Robot(const Robot& o) :
		model(std::make_shared<RobotModel>(o.model)),
		view(std::make_shared<RobotView>(model, o.GetView()->GetShader())) { }
	Robot& operator=(const Robot& o);

	RobotModel* GetModel() const { return model.get(); }
	RobotView* GetView() const { return view.get(); }

	void SetSize(glm::vec2 _s);
	void Render() { view->Render(); }
};

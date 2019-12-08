#pragma once
#include <memory>
#include <vector>
#include <glm/gtc/constants.hpp>
#include "RobotModel.h"
#include "RobotView.h"
#include "Obstacle.h"
#include "ConfigurationSpace.h"

#include "..//Utils/WindowSizeUtils.h"

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
	void ProcessFirstConfiguration(float xpos, float ypos)
	{
		glm::vec2 pos = WindowSizeUtils::ParsePos(xpos, ypos);
		glm::vec4 param = GetNewParametrizations(pos.x, pos.y);

		model->GetStartRef().GetArm1Ref().SetAngle(param.x);
		model->GetStartRef().GetArm2Ref().SetAngle(param.y);

		model->GetStartRef().GetArm1Ref().SetAlthernativeAngle(param.z);
		model->GetStartRef().GetArm2Ref().SetAlthernativeAngle(param.w);
	}

private:
	glm::vec4 GetNewParametrizations(float x, float y)
	{
		float l1 = model->GetStartRef().GetArm1Ref().GetLength();
		float l2 = model->GetStartRef().GetArm2Ref().GetLength();
		float l_square = x * x + y * y;

		float theta2 = 2.f * glm::pi<float>() - glm::acos((l_square - l1 * l1 - l2 * l2) / (2.f * l1 * l2));

		float beta = glm::atan(y, x);
		float phi = glm::acos((l_square + l1 * l1 - l2 * l2) / (2.f * l1 * glm::sqrt(l_square)));
		float theta1 = beta - phi;

		glm::vec4 out;

		out.x = beta + phi;
		out.y = theta2;
		
		out.z = beta - phi;
		out.w = -theta2;

		return out;
	}
};

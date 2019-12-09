#include "Robot.h"

Robot& Robot::operator=(const Robot& o)
{
	model = std::make_shared<RobotModel>(o.model);
	view = std::make_shared<RobotView>(model, o.GetView()->GetShader());

	return *this;
}

void Robot::Render()
{
	view->Render();
	configuration_space->Render();
}

glm::vec4 Robot::GetNewParametrizations(float x, float y)
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

void Robot::ProcessConfiguration(RobotConfiguration& configuration, float xpos, float ypos)
{
	glm::vec2 pos = WindowSizeUtils::ParsePos(xpos, ypos);
	glm::vec4 param = GetNewParametrizations(pos.x, pos.y);

	configuration.GetArm1Ref().SetAngle(param.x);
	configuration.GetArm2Ref().SetAngle(param.y);

	configuration.GetArm1Ref().SetAlthernativeAngle(param.z);
	configuration.GetArm2Ref().SetAlthernativeAngle(param.w);
}

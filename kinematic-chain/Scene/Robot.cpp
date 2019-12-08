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

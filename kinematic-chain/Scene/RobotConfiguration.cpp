#include "RobotConfiguration.h"

RobotConfiguration& RobotConfiguration::operator=(const RobotConfiguration& rc)
{
	arm1 = rc.arm1;
	arm2 = rc.arm2;

	return *this;
}

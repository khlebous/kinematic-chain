#include "RobotModel.h"

RobotModel& RobotModel::operator=(const RobotModel& m)
{
	start = m.start;
	end = m.end;

	return *this;
}

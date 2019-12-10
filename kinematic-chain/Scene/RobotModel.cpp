#include "RobotModel.h"

RobotModel& RobotModel::operator=(const RobotModel& m)
{
	start = m.start;
	end = m.end;
	current = m.current;

	return *this;
}

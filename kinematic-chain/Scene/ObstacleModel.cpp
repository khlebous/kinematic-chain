#include "ObstacleModel.h"

ObstacleModel& ObstacleModel::operator=(const ObstacleModel& o)
{
	position = o.position;
	size = o.size;
	color = o.color;

	return *this;
}

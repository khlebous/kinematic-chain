#include "Arm.h"

Arm& Arm::operator=(const Arm& o)
{
	length = o.length;
	angle = o.angle;
	alternative_angle = o.alternative_angle;
	color = o.color;

	return *this;
}

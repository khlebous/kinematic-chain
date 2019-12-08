#include "Arm.h"

Arm& Arm::operator=(const Arm& o)
{
	length = o.length;
	angle = o.angle;
	color = o.color;

	return *this;
}

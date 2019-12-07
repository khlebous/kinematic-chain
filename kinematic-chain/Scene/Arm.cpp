#include "Arm.h"

Arm& Arm::operator=(const Arm& o)
{
	length = o.length;
	angle = o.angle;

	return *this;
}

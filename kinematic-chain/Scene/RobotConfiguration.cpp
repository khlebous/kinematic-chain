#include "RobotConfiguration.h"

RobotConfiguration::RobotConfiguration() : arm1(Arm()), arm2(Arm()), isAlthernative(false)
{
	isCorrect[0] = true;
	isCorrect[1] = true;
}

RobotConfiguration::RobotConfiguration(const Arm& _a1, const Arm& _a2) : arm1(_a1), arm2(_a2), isAlthernative(false)
{
	isCorrect[0] = true;
	isCorrect[1] = true;
}

RobotConfiguration::RobotConfiguration(const RobotConfiguration& rc) : arm1(rc.arm1), arm2(rc.arm2),
	isAlthernative(rc.isAlthernative)
{
	isCorrect[0] = rc.isCorrect[0];
	isCorrect[1] = rc.isCorrect[1];
}
RobotConfiguration& RobotConfiguration::operator=(const RobotConfiguration& rc)
{
	arm1 = rc.arm1;
	arm2 = rc.arm2;
	isAlthernative = rc.isAlthernative;
	
	isCorrect[0] = rc.isCorrect[0];
	isCorrect[1] = rc.isCorrect[1];

	return *this;
}

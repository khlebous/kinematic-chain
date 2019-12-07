#pragma once
#include "Arm.h"

class RobotConfiguration
{
	Arm arm1;
	Arm arm2;

public:
	RobotConfiguration() : arm1(Arm()), arm2(Arm()) { }
	RobotConfiguration(const Arm& _a1, const Arm& _a2) : arm1(_a1), arm2(_a2) { }
	RobotConfiguration(const RobotConfiguration& rc) : arm1(rc.arm1), arm2(rc.arm2) { }
	RobotConfiguration& operator=(const RobotConfiguration& rc);

	Arm& GetArm1Ref() { return arm1; }
	Arm& GetArm2Ref() { return arm2; }

	void SetArm1(const Arm& _a) { arm1 = _a; }
	void SetArm2(const Arm& _a) { arm2 = _a; }
};

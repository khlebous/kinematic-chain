#pragma once
#include "Arm.h"

class RobotConfiguration
{
	Arm arm1;
	Arm arm2;
	bool isAlthernative;

public:
	RobotConfiguration() : arm1(Arm()), arm2(Arm()), isAlthernative(false) { }
	RobotConfiguration(const Arm& _a1, const Arm& _a2) : arm1(_a1), arm2(_a2), isAlthernative(false) { }
	RobotConfiguration(const RobotConfiguration& rc) : arm1(rc.arm1), arm2(rc.arm2), isAlthernative(rc.isAlthernative) { }
	RobotConfiguration& operator=(const RobotConfiguration& rc);

	Arm& GetArm1Ref() { return arm1; }
	Arm& GetArm2Ref() { return arm2; }
	bool& GetIsAlthernativeRef() { return isAlthernative; }

	void SetArm1(const Arm& _a) { arm1 = _a; }
	void SetArm2(const Arm& _a) { arm2 = _a; }
};

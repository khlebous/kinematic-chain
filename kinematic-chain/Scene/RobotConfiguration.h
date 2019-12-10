#pragma once
#include "Arm.h"

class RobotConfiguration
{
	Arm arm1;
	Arm arm2;
	bool isAlthernative;
	bool isCorrect;

public:
	RobotConfiguration() : arm1(Arm()), arm2(Arm()), isAlthernative(false), isCorrect(true) { }
	RobotConfiguration(const Arm& _a1, const Arm& _a2) : arm1(_a1), arm2(_a2), isAlthernative(false), isCorrect(true) { }
	RobotConfiguration(const RobotConfiguration& rc) : arm1(rc.arm1), arm2(rc.arm2),
		isAlthernative(rc.isAlthernative), isCorrect(rc.isCorrect) { }
	RobotConfiguration& operator=(const RobotConfiguration& rc);

	Arm& GetArm1Ref() { return arm1; }
	Arm& GetArm2Ref() { return arm2; }
	bool& GetIsAlthernativeRef() { return isAlthernative; }
	float GetIsCorrect() const { return isCorrect; }

	void SetArm1(const Arm& _a) { arm1 = _a; }
	void SetArm2(const Arm& _a) { arm2 = _a; }
	void SetIsCorrect(bool _v) { isCorrect = _v; }

	float& GetArm1AngleRef() { return isAlthernative ? arm1.GetAlthernativeAngleRef() : arm1.GetAngleRef(); }
	float& GetArm2AngleRef() { return isAlthernative ? arm2.GetAlthernativeAngleRef() : arm2.GetAngleRef(); }

	float GetArm1Angle() const { return isAlthernative ? arm1.GetAlthernativeAngle() : arm1.GetAngle(); }
	float GetArm2Angle() const { return isAlthernative ? arm2.GetAlthernativeAngle() : arm2.GetAngle(); }
};

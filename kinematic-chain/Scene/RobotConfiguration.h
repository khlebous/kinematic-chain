#pragma once
#include "Arm.h"

class RobotConfiguration
{
	Arm arm1;
	Arm arm2;
	bool isAlthernative;
	bool isCorrect[2];

public:
	RobotConfiguration(); 
	RobotConfiguration(const Arm& _a1, const Arm& _a2);
	RobotConfiguration(const RobotConfiguration& rc);
	RobotConfiguration& operator=(const RobotConfiguration& rc);

	Arm& GetArm1Ref() { return arm1; }
	Arm& GetArm2Ref() { return arm2; }
	bool& GetIsAlthernativeRef() { return isAlthernative; }
	float GetIsCorrect() const { return isAlthernative ? isCorrect[1] : isCorrect[0]; }

	void SetArm1(const Arm& _a) { arm1 = _a; }
	void SetArm2(const Arm& _a) { arm2 = _a; }
	void SetIsCorrect(bool _v) { isCorrect[0] = _v; }
	void SetIsCorrectAlternative(bool _v) { isCorrect[1] = _v; }

	float& GetArm1AngleRef() { return isAlthernative ? arm1.GetAlthernativeAngleRef() : arm1.GetAngleRef(); }
	float& GetArm2AngleRef() { return isAlthernative ? arm2.GetAlthernativeAngleRef() : arm2.GetAngleRef(); }

	float GetArm1Angle() const { return isAlthernative ? arm1.GetAlthernativeAngle() : arm1.GetAngle(); }
	float GetArm2Angle() const { return isAlthernative ? arm2.GetAlthernativeAngle() : arm2.GetAngle(); }

	void Switch() { isAlthernative = !isAlthernative; }
};

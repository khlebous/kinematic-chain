#pragma once

class Arm
{
	float length;
	float angle;

public:
	Arm() : length(0), angle(0) { }
	Arm(float _l, float _a) : length(_l), angle(_a) { }
	Arm(const Arm& o) : length(o.length), angle(o.angle) { }
	Arm& operator=(const Arm& o);

	float& GetLengthRef() { return length; }
	float& GetAngleRef() { return angle; }

	float GetLength() { return length; }
	float GetAngle() { return angle; }

	void SetLength(float _l) { length = _l; }
	void SetAngle(float _a) { angle = _a; }
};

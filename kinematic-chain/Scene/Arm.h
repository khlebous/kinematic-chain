#pragma once
#include <glm/glm.hpp>

class Arm
{
	float length;
	float angle;
	float alternative_angle;
	glm::vec3 color;

public:
	Arm() : length(0), angle(0), alternative_angle(0), color(0) { }
	Arm(float _l, float _a, float _aa, glm::vec3 _c) : length(_l), angle(_a), alternative_angle(_aa), color(_c) { }
	Arm(const Arm& o) : length(o.length), angle(o.angle), alternative_angle(o.alternative_angle), color(o.color) { }
	Arm& operator=(const Arm& o);

	float& GetLengthRef() { return length; }
	float& GetAngleRef() { return angle; }
	float& GetAlthernativeAngleRef() { return alternative_angle; }
	glm::vec3& GetColorRef() { return color; }

	float GetLength() const { return length; }
	float GetAngle() const { return angle; }
	float GetAlthernativeAngle() const { return alternative_angle; }
	glm::vec3 GetColor() const { return color; }

	void SetLength(float _l) { length = _l; }
	void SetAngle(float _a) { angle = _a; }
	void SetAlthernativeAngle(float _aa) { alternative_angle = _aa; }
};

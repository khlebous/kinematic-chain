#pragma once
#include <glm/glm.hpp>

class Arm
{
	float length;
	float angle;
	glm::vec3 color;

public:
	Arm() : length(0), angle(0), color(0) { }
	Arm(float _l, float _a, glm::vec3 _c) : length(_l), angle(_a), color(_c) { }
	Arm(const Arm& o) : length(o.length), angle(o.angle), color(o.color) { }
	Arm& operator=(const Arm& o);

	float& GetLengthRef() { return length; }
	float& GetAngleRef() { return angle; }
	glm::vec3& GetColorRef() { return color; }

	float GetLength() const { return length; }
	float GetAngle() const { return angle; }
	glm::vec3 GetColor() const { return color; }

	void SetLength(float _l) { length = _l; }
};

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class EulerAnglesLimitsUtils
{
	static float minAngle;
	static float maxAngle;
public:
	static bool IsCorrect(const glm::vec3& a)
	{
		if (a.x < minAngle || a.y < minAngle || a.z < minAngle ||
			a.x > maxAngle || a.y > maxAngle || a.z > maxAngle)
			return false;

		return true;
	}

	static size_t GetCorrected(float a)
	{
		int out = a;

		while (out > 360)	out -= 360;
		while (out < 0)	out += 360;

		return (size_t)out;
	}
};

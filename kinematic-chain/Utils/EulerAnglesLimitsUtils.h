#pragma once
#include <glm/glm.hpp>

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

		while (out > maxAngle)	out -= maxAngle;
		while (out < 0)	out += maxAngle;

		return (size_t)out;
	}
};

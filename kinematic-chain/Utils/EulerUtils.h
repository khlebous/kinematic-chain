#pragma once
#include <glm/glm.hpp>

class EulerUtils
{
	static float minAngle;
	static float maxAngle;

public:
	static float GetEulerRotation(float startRot, float endRot, float timePercentage)
	{
		float diffAbs = glm::abs(endRot - startRot);

		auto getValue = [](float endRotValue, float startRotValue, float diffValue)
		{
			if (endRotValue > startRotValue)
			{
				if (diffValue < maxAngle - diffValue)
					return diffValue;
				else
					return diffValue - maxAngle;
			}
			else
			{
				if (diffValue < maxAngle - diffValue)
					return -diffValue;
				else
					return maxAngle - diffValue;
			}
		};

		float diff(getValue(endRot, startRot, diffAbs));

		return diff * timePercentage + startRot;
	}

	static bool IsCorrect(const glm::vec3& a)
	{
		if (a.x < minAngle || a.y < minAngle || a.z < minAngle ||
			a.x > maxAngle || a.y > maxAngle || a.z > maxAngle)
			return false;

		return true;
	}

	static size_t GetCorrectedAngle(float a)
	{
		int out = a;

		while (out > maxAngle)	out -= maxAngle;
		while (out < 0)	out += maxAngle;

		return (size_t)out;
	}
};
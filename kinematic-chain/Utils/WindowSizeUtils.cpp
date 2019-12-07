#include "WindowSizeUtils.h"

glm::vec2 WindowSizeUtils::ParsePos(float xpos, float ypos)
{
	xpos *= 2;
	ypos = 2.0f * (WindowConstants::HEIGHT - ypos);

	return glm::vec2(
		xpos / WindowConstants::WIDTH - 1.0f,
		ypos / WindowConstants::HEIGHT - 1.0f
	);
}

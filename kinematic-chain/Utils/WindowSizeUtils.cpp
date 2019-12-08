#include "WindowSizeUtils.h"

glm::vec2 WindowSizeUtils::ParsePos(float xpos, float ypos)
{
	return glm::vec2(xpos - WindowConstants::WIDTH / 2.0f, WindowConstants::HEIGHT / 2.0f - ypos);
}

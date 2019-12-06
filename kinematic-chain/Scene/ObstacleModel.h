#pragma once
#include <glm/glm.hpp>
#include <memory>

class ObstacleModel
{
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;

public:
	ObstacleModel(glm::vec2 _p, glm::vec2 _s, glm::vec3 _c) : position(_p), size(_s), color(_c) { }
	ObstacleModel(const ObstacleModel& o) : position(o.position), size(o.size), color(o.color) { }
	ObstacleModel(std::shared_ptr<ObstacleModel> o): position(o->position), size(o->size), color(o->color) { }
	~ObstacleModel() { }
	ObstacleModel& operator=(const ObstacleModel& o);

	const glm::vec2& GetPosition() { return position; }
	const glm::vec2& GetSize() { return size; }
	const glm::vec3& GetColor() { return color; }

	glm::vec2& GetPositionRef() { return position; }
	glm::vec2& GetSizeRef() { return size; }
	glm::vec3& GetColorRef() { return color; }

	void SetPosition(const glm::vec2 _p) { position = _p; }
	void SetSize(const glm::vec2 _s) { size = _s; }
	void SetColor(const glm::vec3 _c) { color = _c; }
};

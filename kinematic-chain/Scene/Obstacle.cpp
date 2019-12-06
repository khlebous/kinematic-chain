#include "Obstacle.h"

Obstacle& Obstacle::operator=(const Obstacle& o)
{
	model = std::make_shared<ObstacleModel>(o.model);
	view = std::make_shared<ObstacleView>(model, o.GetView()->GetShader());

	return *this;
}

void Obstacle::SetSize(glm::vec2 _s)
{
	model->SetSize(_s);
	view->UpdateVerticesView();
}

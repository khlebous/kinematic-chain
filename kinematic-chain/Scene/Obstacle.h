#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

#include "Shader.h"
#include "../Utils/ColorConstants.h"
#include "ObstacleView.h"

class Obstacle
{
	std::shared_ptr<ObstacleModel> model;
	std::shared_ptr<ObstacleView> view;

public:
	Obstacle(std::shared_ptr<ObstacleModel> _m, std::shared_ptr<Shader> _s) :
		model(_m), view(std::make_shared<ObstacleView>( _m, _s)) { }
	Obstacle(const Obstacle& o) : 
		model(std::make_shared<ObstacleModel>(o.model)),
		view(std::make_shared<ObstacleView>(model, o.GetView()->GetShader())) { }
	Obstacle& operator=(const Obstacle& o);

	ObstacleView* GetView() const { return view.get(); }
	ObstacleModel* GetModel() const { return model.get(); }

	void SetSize(glm::vec2 _s);
	void Render() { view->Render(); }
};

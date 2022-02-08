#pragma once
#include "glm.hpp"
#include "Shape.h"
#include "LineRenderer.h"
class CollisionData
{
public:
	glm::vec2 worldPos;
	glm::vec2 worldPos2;
	glm::vec2 normal; //Points from A to B
	float depth;

	Shape* shapeA;
	Shape* shapeB;

	void Draw(LineRenderer& lines);
};

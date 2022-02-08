#pragma once
#include "glm.hpp"
#include "Shape.h"
#include "LineRenderer.h"


class Circle
{
public:
	glm::vec2 centre;
	float radius;

	void Draw(LineRenderer& lines);
};

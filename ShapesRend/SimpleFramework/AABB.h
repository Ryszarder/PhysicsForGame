#pragma once

#include <cfloat>
#include "LineRenderer.h"

class AABB
{
public:
	float xMin = FLT_MAX;
	float xMax = -FLT_MAX;
	float yMin = FLT_MAX;
	float yMax = -FLT_MAX;

	AABB() {}
	AABB(float xMinInit, float xMaxInit, float yMinInit, float yMaxInit)
		: xMin(xMinInit), xMax(xMaxInit), yMin(yMinInit), yMax(yMaxInit) {}

	void Draw(LineRenderer& lines);
};
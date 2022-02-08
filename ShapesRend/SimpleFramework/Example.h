#pragma once

#include "GameBase.h"
#include "AABB.h"
#include "Circle.h"
#include "CollisionData.h"


class Example : public GameBase
{
	AABB boxTest;
	Circle circleTest;
	Circle circleTest2;
	CollisionData collisionResult;

public:
	Example();

	void Update();

	void Render();

	void OnMouseClick(int mouseButton);
};
#pragma once
#include "PhysicsObject.h"


class CollisionData
{
public:
	glm::vec2 normal;
	float depth;

	PhysicsObject* shapeA;
	PhysicsObject* shapeB;


	void ResolveCollision();
};
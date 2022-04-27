#pragma once
#include "PhysicsObject.h"

class CollisionData
{
public:
	CollisionData();

	void ResolveCollision();

	PhysicsObject* shapeA = nullptr;
	PhysicsObject* shapeB = nullptr;

	//A to B
	glm::vec2 normal;
	float depth;
};
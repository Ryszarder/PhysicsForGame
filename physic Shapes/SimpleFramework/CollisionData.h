#pragma once
#include "PhysicsObject.h"

class CollisionData
{
public:
	CollisionData();
	~CollisionData();

	void ResolveCollision();

	PhysicsObject* shapeA = nullptr;
	PhysicsObject* shapeB = nullptr;

	glm::vec2 normal;
	//A to B

	float depth;
};
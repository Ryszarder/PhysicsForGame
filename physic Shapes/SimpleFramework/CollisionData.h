#pragma once
#include "PhysicsObject.h"


class CollisionData
{
public:
	CollisionData();
	~CollisionData();

	void ResolveCollision();
	void Draw(LineRenderer& lines);

	PhysicsObject* shapeA = nullptr;
	PhysicsObject* shapeB = nullptr;

	glm::vec2 normal;
	float depth;
	float infinity = std::numeric_limits<float>::max();
};
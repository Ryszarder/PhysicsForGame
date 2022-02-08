#include "CollisionFunctions.h"

CollisionData CollideCircleToBox(const Circle& circle, const AABB& box, LineRenderer& lines)
{
	CollisionData result{};

	glm::vec2 clampedPos = circle.centre;

	if (clampedPos.x < box.xMin) clampedPos.x = box.xMin;
	if (clampedPos.x > box.xMax) clampedPos.x = box.xMax;
	if (clampedPos.y < box.yMin) clampedPos.y = box.yMin;
	if (clampedPos.y > box.yMax) clampedPos.y = box.yMax;

	lines.DrawCircle(clampedPos, 0.1f);

	glm::vec2 circleToClamped = clampedPos - circle.centre;
	float distance = glm::length(circleToClamped);
	result.depth = circle.radius - distance;
	result.normal = circleToClamped / distance;
	result.worldPos = clampedPos;

	return result;
}

CollisionData CollideCircleToCircle(const Circle& shapeA, const Circle& shapeB, LineRenderer& lines)
{
	CollisionData result{};

	glm::vec2 circleToCircle = shapeB.centre - shapeA.centre;
	float distance = glm::length(circleToCircle);
	float radiusTotal = shapeA.radius + shapeB.radius;
	if (distance <= radiusTotal)
	{
		result.depth = shapeB.radius - distance;
		result.normal = circleToCircle / distance;
		result.worldPos = shapeB.centre;
		result.worldPos2 = shapeA.centre;
	}


	return result;
}


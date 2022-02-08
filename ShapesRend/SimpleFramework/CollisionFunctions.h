#pragma once
#include "CollisionData.h"
#include "Circle.h"
#include "AABB.h"

CollisionData CollideCircleToBox(const Circle& circle, const AABB& box, LineRenderer& lines);

CollisionData CollideCircleToCircle(const Circle& shapeA, const Circle& shapeB, LineRenderer& lines);

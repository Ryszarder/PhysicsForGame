#include "Plane.h"
#include <cfloat>

Plane::Plane(glm::vec2 normal, float distance) :
		PhysicsObject(PLANE)
{
	m_distanceToOrigin = distance;
	m_normal = normal;
}

Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float deltaTime) 
{
}

void Plane::Render(LineRenderer& lines)
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	lines.DrawLineSegment(start, end, { 0, 1, 0 });
}
#include "Plane.h"

Plane::Plane(glm::vec2 normal, float distance) :
		PhysicsObject(PLANE)
{
	m_distanceToOrigin = distance;
	m_normal = normal;
	
	//m_distanceToOrigin = -3;
	//m_normal = glm::vec2(0,1);
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

void Plane::resolveCollision(Rigidbody* actor2)
{
	glm::vec2 relativeVelocity = actor2->GetVelocity();

	float m_mass = 10000;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), m_normal) /
		((1 / m_mass) + (1 / actor2->getMass()));

	glm::vec2 force = m_normal * j;
	actor2->applyForce(force);
}

void Plane::ResetPosition()
{
}

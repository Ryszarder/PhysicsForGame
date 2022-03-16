#pragma once
#include "PhysicsObject.h"
#include "Rigidbody.h"

class Plane : public PhysicsObject
{
public:
	Plane(glm::vec2 normal, float distance);
	~Plane();

	virtual void fixedUpdate(glm::vec2 gravity, float deltaTime);
	virtual void Render(LineRenderer& lines);
	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
};
#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity,
		float mass) :
		PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float deltaTime)
{
	m_position += m_velocity * deltaTime;
	applyForce(gravity * m_mass * deltaTime);
}

void Rigidbody::applyForce(glm::vec2 force)
{
	glm::vec2 m_acceleration = force / m_mass;
	m_velocity += m_acceleration;
}

void Rigidbody::Render(LineRenderer& lines)
{
}
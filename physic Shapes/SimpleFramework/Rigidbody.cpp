#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity,
		float mass) :
		PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
}

Rigidbody::~Rigidbody()
{
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

void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force)
{
	applyForce(force);
	actor2->applyForce(-force);
}

void Rigidbody::resolveCollision(Rigidbody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->GetPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->GetVelocity() - m_velocity;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
		((1 / m_mass) + (1 / actor2->getMass()));

	glm::vec2 force = normal * j;
	applyForceToActor(actor2, -force);
}

void Rigidbody::Render(LineRenderer& lines)
{
}
#pragma once
#include "PhysicsObject.h"

class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, 
			glm::vec2 velocity, float mass);
	~Rigidbody(); 

	virtual void fixedUpdate(glm::vec2 gravity, float deltaTime);
	void applyForce(glm::vec2 force);
	void applyPosition(glm::vec2 force);

	virtual void Render(LineRenderer& lines);

	glm::vec2 GetPosition()	{ return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	void SetVelocity(glm::vec2 mPosition) { m_velocity = mPosition; }
	float getMass() { return m_mass; }
	void SetTest(float mTest) { Test = mTest; }
	float GetTest() { return Test; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float Test;
};
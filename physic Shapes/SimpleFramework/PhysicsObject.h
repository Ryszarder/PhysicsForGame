#pragma once
#include <glm.hpp>

enum ShapeType {
	PLANE = 0,
	SPAHRE,
	BOX
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void Render() = 0;
	virtual void ResetPosition() {};

protected:
	ShapeType m_shapeID;
};
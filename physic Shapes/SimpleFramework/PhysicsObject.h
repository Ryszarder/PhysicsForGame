#pragma once
#include <glm.hpp>
#include "LineRenderer.h"

enum ShapeType {
	PLANE = 0,
	SPHERE,/*
	BOX*/
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float deltaTime) = 0;
	virtual void Render(LineRenderer& lines) = 0;
	virtual void ResetPosition() {};
	ShapeType getShapeID() { return m_shapeID; }

protected:
	ShapeType m_shapeID;
};
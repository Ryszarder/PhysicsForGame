#pragma once
#include "Rigidbody.h"


class Sphere : public Rigidbody
{
	Sphere();
	~Sphere();

	virtual void Render();

	float GetRadius() { return m_radius; }
	glm::
};


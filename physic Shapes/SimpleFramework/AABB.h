#pragma once
#include "Rigidbody.h"


class AABB : public Rigidbody
{
public:
	AABB(glm::vec2 position, glm::vec2 velocity, float mass,
		float xMin, float xMax, float yMin, float yMax, glm::vec4 colour);
	~AABB();

	virtual void Render(LineRenderer& lines);

	float GetxMin() { return m_xMin; }
	float GetxMax() { return m_xMax; }
	float GetyMin() { return m_yMin; }
	float GetyMax() { return m_yMax; }


protected:
	float m_xMin;
	float m_xMax;
	float m_yMin;
	float m_yMax;
	glm::vec4 m_colour;
};


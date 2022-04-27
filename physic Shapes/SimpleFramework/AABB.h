#pragma once
#include "Rigidbody.h"

class AABB : public Rigidbody
{
public:
	AABB(glm::vec2 position, glm::vec2 velocity, float mass,
		float width, float height, glm::vec4 colour);

	virtual void Render(LineRenderer& lines);

	float GetxMin() { return m_position.x - m_width / 2.0f; }
	float GetxMax() { return m_position.x + m_width / 2.0f; }
	float GetyMin() { return m_position.y - m_height / 2.0f; }
	float GetyMax() { return m_position.y + m_height / 2.0f; }

protected:
	float m_width;
	float m_height;
	glm::vec4 m_colour;
};
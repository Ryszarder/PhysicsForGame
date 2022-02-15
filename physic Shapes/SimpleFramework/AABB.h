#pragma once
#include "Rigidbody.h"


class AABB : public Rigidbody
{
public:
	AABB(glm::vec2 position, glm::vec2 velocity, float mass,
		glm::vec2 height, glm::vec2 length, glm::vec4 colour);
	~AABB();

	virtual void Render(LineRenderer& lines);



protected:
	glm::vec2 m_height;
	glm::vec2 m_length;
	glm::vec4 m_colour;
};


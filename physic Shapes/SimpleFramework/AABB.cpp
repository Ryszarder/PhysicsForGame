#include "AABB.h"

AABB::AABB(glm::vec2 position, glm::vec2 velocity, float mass,
		glm::vec2 height, glm::vec2 length, glm::vec4 colour) :
		Rigidbody(BOX, position, velocity, 0, mass)
{
	m_height = height;
	m_length = length;
	m_colour = colour;
}

AABB::~AABB()
{
}

void AABB::Render(LineRenderer& lines)
{
	glm::vec2 p1 = m_position - m_length - m_height;
	glm::vec2 p2 = m_position - m_length + m_height;
	glm::vec2 p3 = m_position + m_length + m_height;
	glm::vec2 p4 = m_position + m_length - m_height;
	lines.AddPointToLine(p1);
	lines.AddPointToLine(p2);
	lines.AddPointToLine(p3);
	lines.AddPointToLine(p4);
	lines.FinishLineLoop();
}

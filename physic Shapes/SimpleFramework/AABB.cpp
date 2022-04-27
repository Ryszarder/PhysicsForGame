#include "AABB.h"

AABB::AABB(glm::vec2 position, glm::vec2 velocity, float mass,
			float width, float height, glm::vec4 colour) :
		Rigidbody(BOX, position, velocity, mass)
{
	m_width = width;
	m_height = height;
	m_colour = colour;
}


void AABB::Render(LineRenderer& lines)
{
	lines.AddPointToLine(glm::vec2(m_position.x - m_width * 0.5f, 
					m_position.y - m_height * 0.5f));
	lines.AddPointToLine(glm::vec2(m_position.x - m_width * 0.5f, 
					m_position.y + m_height * 0.5f));
	lines.AddPointToLine(glm::vec2(m_position.x + m_width * 0.5f, 
					m_position.y + m_height * 0.5f));
	lines.AddPointToLine(glm::vec2(m_position.x + m_width * 0.5f, 
					m_position.y - m_height * 0.5f));
	lines.FinishLineLoop();
}
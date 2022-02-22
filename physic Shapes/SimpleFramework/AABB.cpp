#include "AABB.h"

AABB::AABB(glm::vec2 position, glm::vec2 velocity, float mass,
			float xMin, float xMax, float yMin, float yMax, glm::vec4 colour) :
		Rigidbody(BOX, position, velocity, mass)
{
	m_xMin = xMin;
	m_xMax = xMax;
	m_yMin = yMin;
	m_yMax = yMax;
	m_colour = colour;
}

AABB::~AABB()
{
}

void AABB::Render(LineRenderer& lines)
{
	float m_fwidth = m_xMax - m_xMin;
	float m_fheight = m_yMax - m_yMin;

	lines.AddPointToLine(glm::vec2(m_position.x - m_fwidth * 0.5f, 
					m_position.y - m_fheight));
	lines.AddPointToLine(glm::vec2(m_position.x - m_fwidth * 0.5f, 
					m_position.y + m_fheight));
	lines.AddPointToLine(glm::vec2(m_position.x + m_fwidth * 0.5f, 
					m_position.y + m_fheight));
	lines.AddPointToLine(glm::vec2(m_position.x + m_fwidth * 0.5f, 
					m_position.y - m_fheight));
	lines.FinishLineLoop();

	lines.DrawCross(m_position, 1.0f);
}

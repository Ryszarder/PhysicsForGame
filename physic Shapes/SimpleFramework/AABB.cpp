#include "AABB.h"

AABB::AABB(glm::vec2 position, glm::vec2 velocity, float mass,
			float xMin, float xMax, float yMin, float yMax, glm::vec4 colour) :
		Rigidbody(BOX, position, velocity, 0, mass)
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
	//glm::vec2 p1 = m_position - m_xMin - m_yMin;
	//glm::vec2 p2 = m_position - m_xMin + m_yMax;
	//glm::vec2 p3 = m_position + m_xMax + m_yMax;
	//glm::vec2 p4 = m_position + m_xMax - m_yMin;

	glm::vec2 p1 = { m_xMin, m_yMin };
	glm::vec2 p2 = { m_xMin, m_yMax };
	glm::vec2 p3 = { m_xMax, m_yMax };
	glm::vec2 p4 = { m_xMax, m_yMin };

	lines.AddPointToLine(m_position + p1);
	lines.AddPointToLine(m_position + p2);
	lines.AddPointToLine(m_position + p3);
	lines.AddPointToLine(m_position + p4);
	lines.FinishLineLoop();
}

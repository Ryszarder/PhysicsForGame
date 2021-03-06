#include "Sphere.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity,
	float mass, float radius, glm::vec4 colour) :
	Rigidbody(SPHERE, position, velocity, mass)
{
	m_radius = radius;
	m_colour = colour;
}

void Sphere::Render(LineRenderer& lines)
{
	lines.DrawCircle(m_position, m_radius);
}
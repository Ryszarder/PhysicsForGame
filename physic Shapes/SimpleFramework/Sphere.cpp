#include "Sphere.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity,
	float mass, float radius, glm::vec4 colour) :
	Rigidbody(ShapeType::SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::Render(LineRenderer& lines)
{
	lines.DrawCircle(GetPosition(), m_radius);
}

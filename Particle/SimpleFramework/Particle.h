#pragma once

#include "glm.hpp"

#include "LineRenderer.h"

struct Particle
{
public:
	Particle();
	~Particle();
	//Particle(glm::vec2 v_pos, glm::vec2 v_vel);

	void Update(float deltaTime);
	void Render(LineRenderer& line);

private:
	glm::vec2 v_pos;
	glm::vec2 v_vel;
};


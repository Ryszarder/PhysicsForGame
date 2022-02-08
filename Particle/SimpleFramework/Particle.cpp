#include "Particle.h"
#include <random>
#include <math.h>

Particle::Particle()
{
	/*v_vel = {  0.3f,  -0.5f };*/
	v_vel.x = ((((float)rand() / (float)(RAND_MAX)) * 2) - 1);
	v_vel.y = ((((float)rand() / (float)(RAND_MAX)) * 2) - 1);
	v_pos = { -0.0f, -0.0f };


	//v_vel.x = (float)rand() / (float)(RAND_MAX);
	//v_vel.y = (float)rand() / (float)(RAND_MAX);
	//v_pos.x = (float)rand() / (float)(RAND_MAX);
	//v_pos.y = (float)rand() / (float)(RAND_MAX);


	//* by 2 then - 1 for random -1 to 1
	//v_vel.x = ((((float)rand() / (float)(RAND_MAX)) * 2) -1);
	//v_vel.y = ((((float)rand() / (float)(RAND_MAX)) * 2) - 1);
	//v_pos.x = ((((float)rand() / (float)(RAND_MAX)) * 2) - 1);
	//v_pos.y = ((((float)rand() / (float)(RAND_MAX)) * 2) - 1);

	
}

Particle::~Particle()
{
}

//Particle::Particle(glm::vec2 v_pos, glm::vec2 v_vel)
//{
//	//v_vel = { 0.0f, 0.0f };
//	//v_pos = { 0.0f, 0.0f };
//}

void Particle::Update(float deltaTime)
{
	glm::vec2 acc = { 0.0f, -0.05f };
	v_pos += v_vel * deltaTime;
	v_vel += acc * deltaTime;
	
}

void Particle::Render(LineRenderer& lines)
{
	lines.DrawCircle(v_pos, 0.5f, { 1, 0, 0 });

	//lines.DrawCross(v_pos, 0.5f, { 0, 1, 0 });
}

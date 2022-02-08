#pragma once
#include <vector>
#include "Particle.h"
#include "GameBase.h"


class Example : public GameBase
{

public:

	Example();
	~Example();

	void Update();

	void Render();

	void OnMouseClick(int mouseButton);

private:
	std::vector<Particle> particles;
};
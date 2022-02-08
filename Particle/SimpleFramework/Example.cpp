#include "Example.h"
#include "Particle.h"
#include <random>

Example::Example() : GameBase()
{
	//Your initialisation code goes here!
	for (int i = 0; i < 10; i++)
	{
		particles.push_back(Particle());
	}
}

Example::~Example()
{
}

void Example::Update()
{

	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].Update(deltaTime);
	}

	//This call ensures that your mouse position and aspect ratio are maintained as correct.
	GameBase::Update();

	//Your physics (or whatever) code goes here!
	
}

void Example::Render()
{

	//Example code that draws a coloured circle at the mouse position, whose colour depends on which buttons are down.
	if (leftButtonDown)
	{
		lines.DrawCircle(cursorPos, 0.2f, { 1, 0, 0 });
	}
	else if (rightButtonDown)
	{
		lines.DrawCircle(cursorPos, 0.2f, { 0, 1, 0 });
	}
	else
	{
		lines.DrawCircle(cursorPos, 0.2f, { 0, 0, 1 });
	}

	//Your drawing code goes here!

	/*lines.DrawLineSegment({ 0, 0 }, { 5, 10 }, { 0, 1, 0 });*/	//Draw a line from the origin to the point (5.0, 10.0) in green.


	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].Render(lines);
	}

	//This call puts all the lines you've set up on screen - don't delete it or things won't work.
	GameBase::Render();
}

void Example::OnMouseClick(int mouseButton)
{

}

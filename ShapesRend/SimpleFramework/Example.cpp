#include "Example.h"
#include "CollisionFunctions.h"


Example::Example() : GameBase()
{
	//Your initialisation code goes here!
	boxTest = AABB(0, 4, 0, 4);
	circleTest.centre = { 3, 3 };
	circleTest.radius = 1.4f;
	
	//circleTest2.centre = { 0, 0 };
	//circleTest2.radius = 1.4f;
}

void Example::Update()
{
	circleTest.centre = cursorPos;

	collisionResult = CollideCircleToBox(circleTest, boxTest, lines);

	//collisionResult = CollideCircleToCircle(circleTest, circleTest2, lines);
	//This call ensures that your mouse position and aspect ratio are maintained as correct.
	GameBase::Update();

	//Your physics (or whatever) code goes here!

}

void Example::Render()
{
	boxTest.Draw(lines);
	circleTest.Draw(lines);
	circleTest2.Draw(lines);

	collisionResult.Draw(lines);

	//Example code that draws a coloured circle at the mouse position, whose colour depends on which buttons are down.
	/*if (leftButtonDown)
	{
		lines.DrawCircle(cursorPos, 0.2f, { 1, 0, 0 });
	}
	else if (rightButtonDown)
	{
		lines.DrawCircle(cursorPos, 0.2f, { 0, 1, 0 });
	}
	else
	{
		lines.DrawCircle(cursorPos, 0.2f, { 1, 0, 1 });
	}*/

	//Your drawing code goes here!

	//lines.DrawLineSegment({ 0, 0 }, { 5, 10 }, { 0, 1, 0 });	//Draw a line from the origin to the point (5.0, 10.0) in green.


	//This call puts all the lines you've set up on screen - don't delete it or things won't work.
	GameBase::Render();
}

void Example::OnMouseClick(int mouseButton)
{

}

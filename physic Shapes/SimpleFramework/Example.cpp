#include "Example.h"

//Physic Scene
Example::Example() : GameBase()
{
	m_gravity = { 0,-9.82f };
	//Your initialisation code goes here!
	Sphere* ball1 = new Sphere(glm::vec2(3, 0), glm::vec2(0, 0), 4.0f,
						0.5f, glm::vec4(1, 0, 0, 1));
	//Sphere* ball2 = new Sphere(glm::vec2(-3, 0), glm::vec2(1, 0), 3.0f,
	//					0.5, glm::vec4(1, 0, 0, 1));	
	//Sphere* ball3 = new Sphere(glm::vec2(0, 0), glm::vec2(1, 0), 3.0f,
	//					0.5, glm::vec4(1, 0, 0, 1));
	addActor(ball1);
	//addActor(ball2);
	//addActor(ball3);

	//ball1->applyForce(glm::vec2(5, 0));
	//ball2->applyForce(glm::vec2(2, 1));
	//ball3->applyForce(glm::vec2(2, 1));

	Plane* plane = new Plane(glm::vec2(0, 1), -2);

	addActor(plane);
}

Example::~Example()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void Example::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void Example::removeActor(PhysicsObject* actor)
{

}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	Example::plane2Plane,	Example::plane2Sphere,
	Example::sphere2Plane,	Example::sphere2Sphere
};

void Example::Update()
{

	for (int i = 0; i < m_actors.size(); i++)
	{
		//m_actors[i]->Update(deltaTime);
		m_actors[i]->fixedUpdate(m_gravity, deltaTime);
	}
	//This call ensures that your mouse position and aspect ratio are maintained as correct.
	GameBase::Update();

	//Your physics (or whatever) code goes here!
	for (int i = 0; i < m_actors.size(); i++)
	{
		for (int j = i + 1; j < m_actors.size(); j++)
		{
			PhysicsObject* object1 = m_actors[i];
			PhysicsObject* object2 = m_actors[j];
			int shapeId1 = (int)object1->getShapeID();
			int shapeId2 = (int)object2->getShapeID();

			int functionIdx = (shapeId1 * 2) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}
		}
	}
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

/*	lines.DrawLineSegment({ 0, 0 }, { 5, 10 }, { 0, 1, 0 });*/	//Draw a line from the origin to the point (5.0, 10.0) in green.

	for (int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->Render(lines);
	}
	

	//This call puts all the lines you've set up on screen - don't delete it or things won't work.
	GameBase::Render();

	
}

void Example::OnMouseClick(int mouseButton)
{

}

bool Example::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool Example::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return sphere2Plane(obj2, obj1);
}

bool Example::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr)
	{
		float planeOrigin = glm::dot(sphere->GetPosition(), plane->GetNormal());
		float sphereToPlane = planeOrigin - plane->GetDistance();
		float intersection = sphereToPlane - sphere->GetRadius();

		if (intersection < 0)
		{
			sphere->applyForce(-sphere->GetVelocity() * sphere->getMass());
			return true;
		}
	}

	return false;
}

bool Example::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec2 ciricletoCircle = sphere1->GetPosition() - sphere2->GetPosition();
		float distance = glm::length(ciricletoCircle);
		float radiusTotal = sphere1->GetRadius() + sphere2->GetRadius();
		if (distance <= radiusTotal)
		{
			sphere1->SetVelocity(glm::vec2{ 0,0 });
			sphere2->SetVelocity(glm::vec2{ 0,0 });

			return true;
		}
	}

	return false;
}

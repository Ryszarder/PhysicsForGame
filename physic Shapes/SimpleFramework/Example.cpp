#include "Example.h"

//Physic Scene
Example::Example() : GameBase()
{
	m_gravity = { 0, -9.87f };
	//Your initialisation code goes here!
	//Sphere* ball1 = new Sphere(glm::vec2(6, 0), glm::vec2(-2, 0), 4.0f,
	//					0.5f, glm::vec4(1, 0, 0, 1));
	//Sphere* ball2 = new Sphere(glm::vec2(-3, 0), glm::vec2(5, 0), 3.0f,
	//					0.5, glm::vec4(1, 0, 0, 1));	
	//Sphere* ball3 = new Sphere(glm::vec2(0, 0), glm::vec2(1, 0), 3.0f,
	//					0.5, glm::vec4(1, 0, 0, 1));
	//addActor(ball1);
	//addActor(ball2);
	//addActor(ball3);

	Plane* plane1 = new Plane(glm::vec2(0, 1), -4);
	Plane* plane2 = new Plane(glm::vec2(1, 0), -5);
	Plane* plane3 = new Plane(glm::vec2(-1, 0), -8);

	addActor(plane1);
	addActor(plane2);
	addActor(plane3);

	AABB* aabb = new AABB(glm::vec2(0, 0), glm::vec2(0, 0), 40.0f, 
						glm::vec2(0, 1), glm::vec2(1, 0), glm::vec4(1, 0, 0, 1));

	addActor(aabb);
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
	Example::plane2Plane,	Example::plane2Sphere,	Example::plane2AABB,
	Example::sphere2Plane,	Example::sphere2Sphere, Example::sphere2AABB,
	Example::AABB2Plane,	Example::AABB2Sphere,	Example::AABB2AABB,
};

void Example::Update()
{

	for (int i = 0; i < m_actors.size(); i++)
	{
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
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
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

	//Draw a line from the origin to the point (5.0, 10.0) in green.

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

bool Example::plane2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return AABB2Plane(obj2, obj1);
}

bool Example::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr)
	{
		float planeOrigin = glm::dot(sphere->GetPosition(), plane->GetNormal());
		float sphereToPlane = planeOrigin - plane->GetDistance();
		float intersection = sphereToPlane - sphere->GetRadius() ;

		if (intersection < 0)
		{
			plane->resolveCollision(sphere);

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
			sphere1->resolveCollision(sphere2);

			return true;
		}
	}

	return false;
}

bool Example::sphere2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool Example::AABB2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool Example::AABB2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool Example::AABB2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

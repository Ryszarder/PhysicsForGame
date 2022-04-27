#include "Example.h"

//Physic Scene
Example::Example() : GameBase()
{
	//Initialise the value of gravity
	m_gravity = { 0, -9.82f };

	//Initialise the shapes with there vaules in their parameter and
	//adds shape to the back of the vector 
	//Sphere* ball1 = new Sphere(glm::vec2(3, 3), glm::vec2(-4, 0), 4.0f,
	//					0.5f, glm::vec4(1, 0, 0, 1));
	//addActor(ball1);
	//Sphere* ball2 = new Sphere(glm::vec2(-3, 3), glm::vec2(4, 0), 4.0f,
	//					0.5, glm::vec4(1, 0, 0, 1));	
	//addActor(ball2);

	//AABB* aabb1 = new AABB(glm::vec2(-7, 7.1f), glm::vec2(-3, 0), 4.0f,
	//	1.0f, 1.0f, glm::vec4(1, 0, 0, 1));
	//addActor(aabb1);
	//AABB* aabb2 = new AABB(glm::vec2(7, 7), glm::vec2(3, 0), 4.0f,
	//	1.0f, 1.0f, glm::vec4(1, 0, 0, 1));
	//addActor(aabb2);

	Plane* plane1 = new Plane(glm::vec2(0, 1), -8);
	addActor(plane1);
	Plane* plane2 = new Plane(glm::vec2(1, 0), -8);
	addActor(plane2);
	Plane* plane3 = new Plane(glm::vec2(-1, 0), -8);
	addActor(plane3);
	Plane* plane4 = new Plane(glm::vec2(0, -1), -8);
	addActor(plane4);
}

Example::~Example()
{
	//Deletes the shapes when closing application
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void Example::addActor(PhysicsObject* actor)
{
	//Adds the actor to the back of the vector
	m_actors.push_back(actor);
}

void Example::removeActor(PhysicsObject* actor)
{
}

//Creates typedef for collisionData
typedef CollisionData(*fn)(PhysicsObject*, PhysicsObject*);

//Function pointer array 
static fn collisionFunctionArray[] =
{
	Example::plane2Plane,	Example::plane2Sphere,	Example::plane2AABB,
	Example::sphere2Plane,	Example::sphere2Sphere, Example::sphere2AABB,
	Example::AABB2Plane,	Example::AABB2Sphere,	Example::AABB2AABB,
};

void Example::Update()
{
	//For loops that updates the position of the actor
	for (int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->fixedUpdate(m_gravity, deltaTime);
	}

	//Updates GameBase
	GameBase::Update();

	//Checks the collisions to see if any has occurred
	//Runs a for loop in a for loop to shorten the time it takes to check all collisions
	for (int i = 0; i < m_actors.size(); i++)
	{
		for (int j = i + 1; j < m_actors.size(); j++)
		{
			//Initialise the actors and identify the shapes of the actors
			PhysicsObject* object1 = m_actors[i];
			PhysicsObject* object2 = m_actors[j];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			//Picks the function has the two shapes in there parameter
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				//Runs through the collision and if the depth is larger than 0 an collision has occurred
				CollisionData thisCollision = collisionFunctionPtr(object1, object2);
				if (thisCollision.depth > 0)
				{ 
					//Takes the collision and pushes it to the back of the vector
					collisions.push_back(collisionFunctionPtr(object1, object2));
				}	
			}
		}
	}

	//Runs through all the collisions stores in collisions vector
	for (int i = 0; i < collisions.size(); i++)
	{
		collisions[i].ResolveCollision();
	}
	//Clears the vector of all elements inside
	collisions.clear();
}

void Example::Render()
{
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

	//Renders all shapes stored in the actor
	for (int i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->Render(lines);
	}
	
	//Render GameBase
	GameBase::Render();
}

void Example::OnMouseClick(int mouseButton)
{
	if (mouseButton == 0)
	{
		AABB* aabb3 = new AABB(cursorPos, glm::vec2(-3, 0), 4.0f,
			1.0f, 1.0f, glm::vec4(1, 0, 0, 1));
		addActor(aabb3);
	}
	else
	{
		Sphere* ball1 = new Sphere(cursorPos, glm::vec2(-4, 0), 4.0f,
						0.5f, glm::vec4(1, 0, 0, 1));
		addActor(ball1);
	}
}

//Collision check for Plane and Plane
CollisionData Example::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//Since planes are static they return nothing
	CollisionData result{};
	return result;
}

//Collision check plane and sphere
CollisionData Example::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//Changes the order of objects in parameter and runs sphere2Plane function
	return sphere2Plane(obj2, obj1);
}

//Collision check plane and aabb
CollisionData Example::plane2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//Changes the order of objects in parameter and runs aabb2Plane function
	return AABB2Plane(obj2, obj1);
}

//Collision check sphere and plane
CollisionData Example::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	CollisionData result{};

	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr)
	{
		float spherewithNormal = glm::dot(sphere->GetPosition(), plane->GetNormal());
		float intersection = (plane->GetDistance() + sphere->GetRadius()) - spherewithNormal;
		result.depth = intersection;
		result.normal = plane->GetNormal();
		result.shapeA = sphere;
		result.shapeB = plane;
		return result;
	}
	return result;
}

CollisionData Example::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	CollisionData result{};

	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec2 ciricletoCircle = sphere2->GetPosition() - sphere1->GetPosition();
		float distance = glm::length(ciricletoCircle);
		float radiusTotal = sphere1->GetRadius() + sphere2->GetRadius();
		result.depth = radiusTotal - distance;
		result.normal = glm::normalize(ciricletoCircle);
		result.shapeA = sphere1;
		result.shapeB = sphere2;
		return result;
	}
	return result;
}

CollisionData Example::sphere2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	CollisionData result{};

	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	AABB* aabb = dynamic_cast<AABB*>(obj2);

	if (sphere != nullptr && aabb != nullptr)
	{
		glm::vec2 clampedPos = sphere->GetPosition();

		if (clampedPos.x < aabb->GetxMin()) clampedPos.x = aabb->GetxMin();
		if (clampedPos.x > aabb->GetxMax()) clampedPos.x = aabb->GetxMax();
		if (clampedPos.y < aabb->GetyMin()) clampedPos.y = aabb->GetyMin();
		if (clampedPos.y > aabb->GetyMax()) clampedPos.y = aabb->GetyMax();

		glm::vec2 sphereToClamped = clampedPos - sphere->GetPosition();
		float distance = glm::length(sphereToClamped);
		if (distance < 0.00001f)
		{
			glm::vec2 sphereToBox = aabb->GetPosition() - sphere->GetPosition();
			float dist = glm::length(sphereToBox);
			result.depth = sphere->GetRadius() - dist;
			result.normal = glm::normalize(sphereToBox);
			result.shapeA = sphere;
			result.shapeB = aabb;
			return result;
		}
		else
		{
			result.depth = sphere->GetRadius() - distance;
			result.normal = sphereToClamped / distance;
			result.shapeA = sphere;
			result.shapeB = aabb;
			return result;
		}
	}
	return result;
}

CollisionData Example::AABB2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	CollisionData result{};

	AABB* aabb = dynamic_cast<AABB*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (aabb != nullptr && plane != nullptr)
	{
		glm::vec2 topLeft = { aabb->GetxMin(), aabb->GetyMax() };
		glm::vec2 topRight = { aabb->GetxMax(), aabb->GetyMax() };
		glm::vec2 bottomLeft = { aabb->GetxMin(), aabb->GetyMin() };
		glm::vec2 bottomRight = { aabb->GetxMax(), aabb->GetyMin() };

		float boxwithNormal1 = glm::dot(topLeft, plane->GetNormal());
		float overlap1 = plane->GetDistance() - boxwithNormal1;

		float boxwithNormal2 = glm::dot(topRight, plane->GetNormal());
		float overlap2 = plane->GetDistance() - boxwithNormal2;

		float boxwithNormal3 = glm::dot(bottomLeft, plane->GetNormal());
		float overlap3 = plane->GetDistance() - boxwithNormal3;

		float boxwithNormal4 = glm::dot(bottomRight, plane->GetNormal());
		float overlap4 = plane->GetDistance() - boxwithNormal4;

		if (overlap1 > overlap2 && overlap1 > overlap3 && overlap1 > overlap4)
		{
			if (overlap1 > 0)
			{
				result.depth = overlap1;
				result.normal = plane->GetNormal();
				result.shapeA = aabb;
				result.shapeB = plane;
				return result;
			}
		}
		else if (overlap2 > overlap3 && overlap2 > overlap4)
		{
			if (overlap2 > 0)
			{
				result.depth = overlap2;
				result.normal = plane->GetNormal();
				result.shapeA = aabb;
				result.shapeB = plane;
				return result;
			}
		}
		else if (overlap3 > overlap4)
		{
			if (overlap3 > 0)
			{
				result.depth = overlap3;
				result.normal = plane->GetNormal();
				result.shapeA = aabb;
				result.shapeB = plane;
				return result;
			}
		}
		else
		{
			if (overlap4 > 0)
			{
				result.depth = overlap4;
				result.normal = plane->GetNormal();
				result.shapeA = aabb;
				result.shapeB = plane;
				return result;
			}
		}
	}
	return result;
}

CollisionData Example::AABB2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return sphere2AABB(obj2, obj1);
}

CollisionData Example::AABB2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	CollisionData result{};

	AABB* aabb1 = dynamic_cast<AABB*>(obj1);
	AABB* aabb2 = dynamic_cast<AABB*>(obj2);

	if (aabb1 != nullptr && aabb2 != nullptr)
	{
		float xOverlap1 = aabb1->GetxMax() - aabb2->GetxMin();
		float xOverlap2 = aabb2->GetxMax() - aabb1->GetxMin();

		float yOverlap1 = aabb1->GetyMax() - aabb2->GetyMin();
		float yOverlap2 = aabb2->GetyMax() - aabb1->GetyMin();

		if (xOverlap1 < xOverlap2 && xOverlap1 < yOverlap1 && xOverlap1 < yOverlap2)
		{
			result.depth = xOverlap1;
			result.normal = glm::vec2(1, 0);
			result.shapeA = aabb1;
			result.shapeB = aabb2;
			return result;
		}
		else if (xOverlap2 < yOverlap1 && xOverlap2 < yOverlap2)
		{
			result.depth = xOverlap2;
			result.normal = glm::vec2(-1, 0);
			result.shapeA = aabb1;
			result.shapeB = aabb2;
			return result;
		}
		else if (yOverlap1 < yOverlap2)
		{
			result.depth = yOverlap1;
			result.normal = glm::vec2(0, 1);
			result.shapeA = aabb1;
			result.shapeB = aabb2;
			return result;
		}
		else
		{
			result.depth = yOverlap2;
			result.normal = glm::vec2(0, -1);
			result.shapeA = aabb1;
			result.shapeB = aabb2;
			return result;
		}
	}
	return result;
}
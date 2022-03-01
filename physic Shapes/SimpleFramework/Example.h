#pragma once
//Headers
#include "GameBase.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"
#include "CollisionData.h"


class Example : public GameBase
{
public:
	//Constructor
	Example();
	//Destructer
	~Example();

	//Adds shapes to the back of an vector 
	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);

	//Updates functions and variable
	void Update();

	//Draws Shapes
	void Render();

	void OnMouseClick(int mouseButton);

	//Function pointer tables for collision detection
	static CollisionData plane2Plane(PhysicsObject*, PhysicsObject*);
	static CollisionData plane2Sphere(PhysicsObject*, PhysicsObject*);
	static CollisionData plane2AABB(PhysicsObject*, PhysicsObject*);
	static CollisionData sphere2Plane(PhysicsObject*, PhysicsObject*);
	static CollisionData sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static CollisionData sphere2AABB(PhysicsObject*, PhysicsObject*);
	static CollisionData AABB2Plane(PhysicsObject*, PhysicsObject*);
	static CollisionData AABB2Sphere(PhysicsObject*, PhysicsObject*);
	static CollisionData AABB2AABB(PhysicsObject*, PhysicsObject*);

protected:
	//Creates variables
	glm::vec2 m_gravity;
	std::vector<PhysicsObject*> m_actors;
	std::vector<CollisionData> collisions;
};
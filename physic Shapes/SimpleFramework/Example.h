#pragma once

#include "GameBase.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"


class Example : public GameBase
{


public:
	Example();
	~Example();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void Update();

	void Render();

	void OnMouseClick(int mouseButton);

	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2AABB(PhysicsObject*, PhysicsObject*);
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool sphere2AABB(PhysicsObject*, PhysicsObject*);
	static bool AABB2Plane(PhysicsObject*, PhysicsObject*);
	static bool AABB2Sphere(PhysicsObject*, PhysicsObject*);
	static bool AABB2AABB(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2 m_gravity;
	std::vector<PhysicsObject*> m_actors;
};
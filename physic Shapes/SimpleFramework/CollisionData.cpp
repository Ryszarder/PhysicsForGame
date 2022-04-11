#include "CollisionData.h"
#include "Rigidbody.h"

CollisionData::CollisionData()
{

}

CollisionData::~CollisionData()
{
}

void CollisionData::ResolveCollision()
{
	Rigidbody* rigidA = dynamic_cast<Rigidbody*>(shapeA);
	Rigidbody* rigidB = dynamic_cast<Rigidbody*>(shapeB);

	if (rigidA && rigidB)
	{
		glm::vec2 relativeVelocity = rigidB->GetVelocity() - rigidA->GetVelocity();

		float elasticity = 1;
		float relativeVelocityDot = dot(relativeVelocity, normal);
		if (relativeVelocityDot > 0) return;
		float j = -(1 + elasticity) * relativeVelocityDot /
			((1 / rigidA->getMass()) + (1 / rigidB->getMass()));

		glm::vec2 force = normal * j;

		rigidA->applyForce(-force);
		rigidB->applyForce(force);
	}
	else if (!(rigidA == nullptr && rigidB == nullptr))
	{
		//One is a plane! Do something else!
		Rigidbody* rigid = (rigidA != nullptr) ? rigidA : rigidB;

		glm::vec2 relativeVelocity = rigid->GetVelocity();

		float elasticity = 1;
		float relativeVelocityDot = dot(relativeVelocity, normal);
		if (relativeVelocityDot > 0) return;
		float j = -(1 + elasticity) * relativeVelocityDot /
				(1 / rigid->getMass());

		glm::vec2 force = normal * j;
		rigid->applyForce(force);;
	}
}
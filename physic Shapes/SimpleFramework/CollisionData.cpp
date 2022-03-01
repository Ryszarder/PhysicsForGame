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
	//One of these might be null now, because it's a plane!
	//We need to write a bunch of shitty branching code to hanedle this.

	if (rigidA && rigidB)
	{

		//glm::vec2 normal = glm::normalize(rigidB->GetPosition() - rigidA->GetPosition());
		//only true for circle to circle

		glm::vec2 relativeVelocity = rigidB->GetVelocity() - rigidA->GetVelocity();

		float elasticity = 1;
		float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
			((1 / rigidA->getMass()) + (1 / rigidB->getMass()));

		glm::vec2 force = normal * j;

		rigidA->applyForce(-force);
		rigidB->applyForce(force);
	}
	else if (!(rigidA == nullptr && rigidB == nullptr))
	{
		//One is a plane! Do something else!
		Rigidbody* rigid = (rigidA != nullptr) ? rigidA : rigidB;

		//Same logic as above, but only apply the force to 'rigid' (the one that's not a plane).
		//When you do the maths, you'll assume the velocity of the other one is zero, and the mass is infinity
		//Thus 1 / mass will be treated as zero.


		glm::vec2 relativeVelocity = rigid->GetVelocity();


		float elasticity = 1;
		float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
				(1 / rigid->getMass());

		glm::vec2 force = normal * j;
		rigid->applyForce(force);;
	}
	//int x = 1;
	//
	//int y = ((x < 2) ? 5 : 7);
	//
	//int y;
	//if (x < 2)
	//{
	//	y = 5;
	//}
	//else
	//{
	//	y = 7;
	//}
}

void CollisionData::Draw(LineRenderer& lines)
{

}



//1.Vitual void getVel and Applyforce to pysicobject
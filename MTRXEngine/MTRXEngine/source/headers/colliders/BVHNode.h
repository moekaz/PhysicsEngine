/*
	Setting up a bounding volume hierarchy for broad phase collision detection
*/

#pragma once

#include <entities/Body.h>
#include <colliders/Collider.h>

namespace mtrx
{
	// Potential collision with bodies (dunno if we do this with bodies(particles and rigidbodies or just rigidbodies))
	struct PotentialCollision
	{
		Body* bodies[2];
	};

	class BVHNode
	{
	public:
		BVHNode* children[2]; // Left and right children
		Collider* boundingVolume; // the bounding volume used 

		BVHNode();
		~BVHNode();
	};
}

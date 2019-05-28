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

	template<class IBoundingVolume>
	class BVHNode
	{
	public:
		BVHNode* parent; // Parent node
		BVHNode* children[2]; // Left and right children
		IBoundingVolume boundingVolume; // The bounding volume used 
		Body* body; // Only leaves will have rigidbodies (we can use an unordered_map to get corresponding rigidbodies if we want)

		BVHNode(BVHNode* parent, IBoundingVolume& volume, Body* body = nullptr);
		~BVHNode();

		inline bool IsLeaf() { return !children[0] && !children[1]; }
		void GetPotentialContacts(std::list<PotentialCollision>& potentialCollisions);
		bool IsCollision(BVHNode& other);
		void Insert(Body* body, Collider& collider);
		void RecalculateBoundingVolume();
	};
}

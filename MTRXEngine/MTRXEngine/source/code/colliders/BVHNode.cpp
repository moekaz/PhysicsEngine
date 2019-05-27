#include "PrecompiledHeader.h"
#include "colliders/BVHNode.h"

namespace mtrx
{
	BVHNode::BVHNode(BVHNode* parent, Collider* collider, Body* body = nullptr) : parent(parent), boundingVolume(collider), body(body)
	{}

	BVHNode::~BVHNode()
	{}

	void BVHNode::GetPotentialContacts(std::list<PotentialCollision>& potentialCollisions)
	{
		// We have a leaf we cannot generate potential contacts
		if (IsLeaf())
			return;

		// Check for collision between the 2 children of this node

	}

	bool BVHNode::IsCollision(BVHNode& other)
	{
		other.boundingVolume->CheckCollision(*other.boundingVolume);
	}

	void BVHNode::Insert() 
	{
	}

	void BVHNode::RecalculateBoundingVolume() 
	{
	}
}
#include "PrecompiledHeader.h"
#include "colliders/BVHNode.h"

namespace mtrx
{
	template<class IBoundingVolume>
	BVHNode<IBoundingVolume>::BVHNode(BVHNode* parent, IBoundingVolume& collider, Body* body) : parent(parent), boundingVolume(collider), body(body)
	{}

	template<class IBoundingVolume>
	BVHNode<IBoundingVolume>::~BVHNode()
	{
		// Some work needs to be done here
	}

	template<class IBoundingVolume>
	void BVHNode<IBoundingVolume>::GetPotentialContacts(std::list<PotentialCollision>& potentialCollisions)
	{
		// We have a leaf we cannot generate potential contacts
		if (IsLeaf())
			return;

		// Check for collision between the 2 children of this node

	}

	template<class IBoundingVolume>
	bool BVHNode<IBoundingVolume>::IsCollision(BVHNode& other)
	{
		other.boundingVolume->CheckCollision(*other.boundingVolume);
	}

	template<class IBoundingVolume>
	void BVHNode<IBoundingVolume>::Insert(Body* body, Collider& collider)
	{
		// Inserting a new BVH into the hierarchy
		BVHNode* currentNode = this;
		while (!currentNode->IsLeaf())
		{
			// we would go in the direction with the least growth
			if (children[0]->boundingVolume->GetGrowth() < children[1]->boundingVolume->GetGrowth())
				currentNode = children[0];
			else
				currentNode = children[1];
		}

		// This is not gonna work
		// No longer a leaf
		currentNode->children[0] = new BVHNode(currentNode, boundingVolume, currentNode->body);
		currentNode->children[1] = new BVHNode(currentNode, &collider, body);

		currentNode->body = nullptr;
		
		// Recalculate bounding volume
		RecalculateBoundingVolume();
	}

	template<class IBoundingVolume>
	void BVHNode<IBoundingVolume>::RecalculateBoundingVolume() 
	{
		// Rebuild the bounding volume

	}
}
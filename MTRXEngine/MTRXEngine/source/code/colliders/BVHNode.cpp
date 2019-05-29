#include "PrecompiledHeader.h"
#include "colliders/BVHNode.h"

namespace mtrx
{
	template<class BoundingVolume>
	BVHNode<BoundingVolume>::BVHNode(BVHNode* parent, BoundingVolume& collider, Body* body) : parent(parent), boundingVolume(collider), body(body)
	{}

	template<class BoundingVolume>
	BVHNode<BoundingVolume>::~BVHNode()
	{
		// Some work needs to be done here
	}

	template<class BoundingVolume>
	void BVHNode<BoundingVolume>::GetPotentialContacts(std::list<PotentialCollision>& potentialCollisions)
	{
		// We have a leaf we cannot generate potential contacts
		if (IsLeaf())
			return;

		// Check for collision between the 2 children of this node

	}

	template<class BoundingVolume>
	bool BVHNode<BoundingVolume>::IsCollision(BVHNode& other)
	{
		other.boundingVolume->CheckCollision(*other.boundingVolume);
	}

	template<class BoundingVolume>
	void BVHNode<BoundingVolume>::Insert(Body* body, Collider& collider)
	{
		// Inserting a new BVH into the hierarchy
		BVHNode* currentNode = this;
		while (!currentNode->IsLeaf())
		{
			// we would go in the direction with the least growth
			if (children[0]->boundingVolume->GetGrowth(collider) < children[1]->boundingVolume->GetGrowth(collider))
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

	template<class BoundingVolume>
	void BVHNode<BoundingVolume>::RecalculateBoundingVolume()
	{
		// Rebuild the bounding volume
		if (Isleaf())
			return;

		BVHNode* currentNode = this;
		while (currentNode)
		{
			currentNode->boundingVolume = IBoundingVolume(currentNode->children[0]->boundingVolume, currentNode->children[1]->boundingVolume);
			currentNode = currentNode->parent; // Go up the tree
		}
	}
}
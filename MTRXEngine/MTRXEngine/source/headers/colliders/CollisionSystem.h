/*
*/

#pragma once

#include <colliders/BVHNode.h>
#include <../code/colliders/BVHNode.cpp>
#include <colliders/SphereCollider.h>
#include <colliders/BoxCollider.h>

namespace mtrx
{
	class CollisionSystem
	{
	public:
		CollisionSystem();
		~CollisionSystem();

		// Using sphere colliders atm
		BVHNode<SphereCollider>* root;
	};
}

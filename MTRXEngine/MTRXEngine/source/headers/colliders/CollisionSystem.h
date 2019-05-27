/*
*/
#pragma once

#include <colliders/BVHNode.h>

namespace mtrx
{
	class CollisionSystem
	{
	public:
		CollisionSystem();
		~CollisionSystem();

		BVHNode root;
	};
}

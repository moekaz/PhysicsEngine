/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>

namespace mtrx
{
	// Forward declarations
	class BoxCollider;
	class CapsulesCollider;
	class MeshCollider;

	class SphereCollider : public Collider
	{
	public:
		float radius;

		SphereCollider(const glm::vec3& vec = glm::vec3(), float radius = 0.5);
		~SphereCollider();

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;
	};
}
/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>

namespace mtrx
{
	// Forward declarations
	class BoxCollider;
	class CapsulesCollider;
	class MeshCollider;

	class SphereCollider : public Collider, public IBoundingVolume
	{
	public:
		float radius;

		// TODO: add position scale and orientation to constructor 
		SphereCollider(const glm::vec3& center = glm::vec3(), float radius = 0.5);
		SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2);
		~SphereCollider();

		float GetGrowth(const SphereCollider&);

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;

		virtual inline void SetScale(const glm::vec3& scale) override
		{
			// TODO: Add some documentation about this
			// Using only x value of the scale
			Collider::SetScale(scale);
			radius = 0.5f * scale.x;
		}
	};
}
/*
	Author: Mohamed Kazma
	Description: An implementation of a box collider
*/

#pragma once

#include <colliders/ConvexShapeCollider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>

namespace mtrx
{
	// Forward declarations
	class SphereCollider;
	class CapsuleCollider;
	class MeshCollider;

	class BoxCollider : public ConvexShapeCollider, public IBoundingVolume
	{
	public:
		glm::vec3 halfExtents;

		// TODO: This needs to be updated with transform information and other info
		BoxCollider(const glm::vec3& = glm::vec3());
		BoxCollider(const BoxCollider& collider1, const BoxCollider& collider2);
		~BoxCollider();

		virtual bool CheckCollision(const mtrx::Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;

		float GetGrowth(const BoxCollider& boxCollider);

		inline const glm::vec3* GetAxes() const { return axes.axes; }

	private:
		ObjectAxes axes;
	};
}
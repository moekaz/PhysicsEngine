#pragma once

#include <colliders/Collider.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/IBoundingVolume.h>
#include <math/Transform.h>

namespace mtrx
{
	class SphereCollider : public Collider, public IBoundingVolume
	{
	public:
		SphereCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radius = 0.5);
		SphereCollider(const Transform& transform = Transform(), float radius = 0.5);
		SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2); // Used for BVH construction
		virtual ~SphereCollider() = default;

		virtual inline bool RaycastCollision(const Ray& ray) override { return RaycastCollisionUtil::RaySphereCollision(GetPosition(), radius, ray.startPosition, ray.direction); }
		virtual inline float GetSize() override { return 1.333333f * PI * radius * radius * radius; }
		virtual inline float GetGrowth(const SphereCollider& sphereCollider) { return SQR(SphereCollider(*this, sphereCollider).radius) - SQR(radius); }

		inline float GetRadius() const { return radius; }

		inline void SetRadius(float radius)
		{
			this->radius = radius;
			transform.GetScale().x = radius * 2.f;
		}

		// Only the X coordinate of the scale affects the collider
		virtual inline void SetScale(const glm::vec3& scale) override
		{
			Collider::SetScale(scale);
			radius = 0.5f * scale.x;
		}

	private:
		float radius;
	};
}
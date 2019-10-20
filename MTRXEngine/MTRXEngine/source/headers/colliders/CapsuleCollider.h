#pragma once

#include <Defs.h>
#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>

namespace mtrx
{
	class CapsuleCollider : public Collider
	{
	public:
		float radii;
		glm::vec3 A;
		glm::vec3 B;
		float height;

		// TBD: THIS IS PRETTY BROKEN NEEDS TO BE WORKED ON
		CapsuleCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radii = 0.5f, float height = 1.f);
		CapsuleCollider(const Transform& transform = Transform(), float radii = 0.5f, float height = 1.f);
		virtual ~CapsuleCollider() = default;

		virtual bool RaycastCollision(const Ray& ray) override { return CollisionUtil::RayCapsuleCollision(ray.startPosition, ray.direction, A, B, radii); }

		virtual inline void SetScale(const glm::vec3& scale) override
		{
			// NOTE: WE ARE ONLY USING THE X AND Y VALUES OF THE SCALE FOR SCALING THE COLLIDER
			Collider::SetScale(scale);
			height = 1.f * scale.y;
			radii = 0.5f * scale.x;
			A = GetPosition() - GetUp() * (height / 2);
			B = GetPosition() + GetUp() * (height / 2);
		}

		virtual inline void SetPosition(const glm::vec3& position) override
		{
			glm::vec3 difference = position - GetPosition();
			Collider::SetPosition(position);
			A += difference;
			B += difference;
		}

		virtual inline void SetOrientation(const glm::quat& orientation) override
		{
			Collider::SetOrientation(orientation);
			A = GetPosition() - GetUp() * (height / 2);
			B = GetPosition() + GetUp() * (height / 2);
		}
	};
}
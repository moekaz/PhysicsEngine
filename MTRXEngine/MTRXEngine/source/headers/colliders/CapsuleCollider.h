/*
	Author: Mohamed Kazma
	Description: Capsule colliders
*/

#pragma once

#include <Defs.h>
#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>

namespace mtrx
{
	class CapsuleCollider : public Collider, IBoundingVolume
	{
	public:
		float radii;
		glm::vec3 A;
		glm::vec3 B;
		float height;

		// TODO: Look into Capsule collider parameter information and add position orientation etc...
		CapsuleCollider(const glm::vec3& center = glm::vec3(), float radii = 0.5f, float height = 1.f);
		CapsuleCollider(const CapsuleCollider& collider1, const CapsuleCollider& collider2);
		~CapsuleCollider();

		float GetGrowth(const CapsuleCollider& capsuleCollider);

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;

		virtual inline void SetScale(const glm::vec3& scale) override
		{
			// TODO: Implement this
			// WE are only using x and y values for scales
			Collider::SetScale(scale);
			height = 1.f * scale.y;
			radii = 0.5f * scale.x;
			A = transform.position - GetUp() * (height / 2);
			B = transform.position + GetUp() * (height / 2);
		}

		virtual inline void SetPosition(const glm::vec3& position) override
		{
			// TODO: Implement this
			Collider::SetPosition(position);
			A = transform.position - GetUp() * (height / 2);
			B = transform.position + GetUp() * (height / 2);
		}

		virtual inline void SetRotation(const glm::quat& orientation)
		{
			// TODO: Implement this
			Collider::SetRotation(orientation);
			A = A * transform.orientation;
			B = B * transform.orientation;
		}
	};
}
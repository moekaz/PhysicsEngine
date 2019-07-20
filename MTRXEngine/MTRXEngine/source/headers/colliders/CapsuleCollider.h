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

		CapsuleCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radii = 0.5f, float height = 1.f);
		CapsuleCollider(const Transform& transform = Transform(), float radii = 0.5f, float height = 1.f);
		CapsuleCollider(const CapsuleCollider& collider1, const CapsuleCollider& collider2);
		~CapsuleCollider();

		float GetGrowth(const CapsuleCollider& capsuleCollider);

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;

		virtual inline void SetScale(const glm::vec3& scale) override
		{
			// NOTE: WE ARE ONLY USING THE X AND Y VALUES OF THE SCALE FOR SCALING THE COLLIDER
			Collider::SetScale(scale);
			height = 1.f * scale.y;
			radii = 0.5f * scale.x;
			A = transform.position - GetUp() * (height / 2);
			B = transform.position + GetUp() * (height / 2);
		}

		virtual inline void SetPosition(const glm::vec3& position) override
		{
			// TBD: This can be done a whole lot better
			glm::vec3 difference = position - transform.position;
			Collider::SetPosition(position);
			A += difference;
			B += difference;

			//A = transform.position - GetUp() * (height / 2);
			//B = transform.position + GetUp() * (height / 2);
		}

		virtual inline void SetRotation(const glm::quat& orientation)
		{
			// TBD: Rotation setting for capsule colliders is incorrect it seems
			Collider::SetRotation(orientation);
			A = A * transform.orientation;
			B = B * transform.orientation;
		}
	};
}
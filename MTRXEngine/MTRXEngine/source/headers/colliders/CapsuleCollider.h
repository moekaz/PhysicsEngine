/*
	Author: Mohamed Kazma
	Description: Capsule colliders
*/

#pragma once

#include <Defs.h>
#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>

namespace mtrx
{
	class CapsuleCollider : public Collider
	{
	public:
		float radii;
		glm::vec3 A;												
		glm::vec3 B;
		float height;

		CapsuleCollider(const glm::vec3& = glm::vec3(), float radii = 0.25f, float height = 0.5f);
		~CapsuleCollider();

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;
		virtual float GetSize() override;
	};
}
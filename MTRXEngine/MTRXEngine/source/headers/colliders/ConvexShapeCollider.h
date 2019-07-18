/*
	Author: Mohamed Kazma
	Description: Colliders with a convex shape (GJK is what is being used for collision detection)
*/

#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>

namespace mtrx
{
	class ConvexShapeCollider : public Collider
	{
	public:
		std::vector<glm::vec3*> vertices;

		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const glm::vec3& = glm::vec3());
		~ConvexShapeCollider();

		virtual bool CheckCollision(const Collider&) override;
		virtual bool RaycastCollision(const Ray&) override;

		// Vertices and model matrices
		std::vector<glm::vec3*> GetVertices() const;
		glm::mat4 GetModelMatrix() const;

		// Used for GJK minkowski sum calculations
		glm::vec3 Support(const ConvexShapeCollider&, const glm::vec3&) const;
		glm::vec3& FarthestPointInDirection(const glm::vec3&) const;
	};
}
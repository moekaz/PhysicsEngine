/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
	PS: Calls for collision detection should be done b4 calling the updating functions
*/

#pragma once

#include <Defs.h>
#include <Ray.h>

namespace mtrx
{
	class Collider
	{
	public:	
		Collider(const ColliderType& colliderType, const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1), bool isConvex = false);
		Collider(const ColliderType& colliderType, const Transform& transform, bool isConvex = false);
		~Collider();										
		
		virtual bool CheckCollision(const Collider&) = 0;
		virtual bool RaycastCollision(const Ray&) = 0;

		// Getters
		inline const glm::vec3& GetPosition() const { return transform.position; }
		inline const ColliderType& GetColliderType() const { return type; }
		inline const int GetColliderId() const { return colliderId; }
		inline const bool IsConvex() const { return isConvexShape; }

		// TODO: this is a little expensive
		inline glm::vec3 GetForward() { return glm::normalize(transform.orientation * axes[0]); }
		inline glm::vec3 GetSide() { return glm::normalize(transform.orientation * axes[1]); }
		inline glm::vec3 GetUp() { return glm::normalize(transform.orientation * axes[2]); }

		// Setters
		virtual inline void SetPosition(const glm::vec3& center) { transform.position = center; }
		virtual inline void SetScale(const glm::vec3& scale) { transform.scale = scale; }
		virtual inline void SetRotation(const glm::quat& orientation) { transform.orientation = orientation; }
	
	private:
		static int id;

	protected:
		int colliderId;
		ColliderType type;
		bool isConvexShape;
		Transform transform;
		ObjectAxes axes; // The axes that define this collider's world
	};
}
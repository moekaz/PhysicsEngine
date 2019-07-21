/*
	Author: Mohamed Kazma
	Description: Implementation of a convex shape collider
*/

#include <PrecompiledHeader.h>
#include <colliders/ConvexShapeCollider.h>

namespace mtrx
{
	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) : 
		Collider(colliderType, center, orientation, scale, true) 
	{}

	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const Transform& transform) : 
		Collider(colliderType, transform, true)
	{}

	ConvexShapeCollider::~ConvexShapeCollider()
	{
		for (int i = 0; i < vertices.size(); ++i)
		{
			delete vertices[i];
		}
	}

	// Used for GJK collision
	glm::vec3 ConvexShapeCollider::Support(const ConvexShapeCollider& convexCollider, const glm::vec3& direction) const
	{
		glm::vec3& p1 = FarthestPointInDirection(direction);
		glm::vec3& p2 = convexCollider.FarthestPointInDirection(-direction);
		glm::vec3 p3 = p1 - p2;
		return p3;
	}

	// Return farthest point with respect to a certain direction
	glm::vec3& ConvexShapeCollider::FarthestPointInDirection(const glm::vec3& direction) const
	{
		float maxDot = -std::numeric_limits<float>::infinity();	// Max dot vector
		glm::vec3* farthest = nullptr;	// Farthest vector

		std::vector<glm::vec3*> verts = GetVertices();
		for (unsigned int i = 0; i < verts.size(); ++i)
		{
			float dot = glm::dot(*verts[i], direction);
			if (dot > maxDot)
			{
				maxDot = dot;
				farthest = verts[i];
			}
		}

		// TBD: THIS WILL NOT WORK
		for (int i = 0; i < verts.size(); ++i)
		{
			delete verts[i];
		}

		// Check that we have a vertex to use
		assert(farthest);
		return *farthest;
	}

	// Convex shape collision detection
	bool ConvexShapeCollider::CheckCollision(const Collider& col)
	{
		// TBD: Collision detection architecture is ugly and needs to be redone
		if (col.IsConvex())
		{
			const ConvexShapeCollider& collider = static_cast<const ConvexShapeCollider&>(col);
			return CollisionUtil::ConvexShapeCollision(*this, collider);	// Collision
		}
		else 
			return false;
	}

	bool ConvexShapeCollider::RaycastCollision(const Ray& ray)
	{
		// A ray is a convex shape if we use it as a line
		glm::vec3 rayEndPoint = glm::normalize(ray.direction) * MAX_RAY_SIZE;	// Get the end point of the ray
		ConvexShapeCollider convexLine = ConvexShapeCollider(ColliderType::ConvexShape, rayEndPoint - ray.startPosition);	// Setup the convex shape
		glm::vec3 start = ray.startPosition;

		//convexLine.vertices.reserve(2);
		//convexLine.vertices.emplace_back(&start);
		//convexLine.vertices.emplace_back(&rayEndPoint);

		return CollisionUtil::ConvexShapeCollision(*this, convexLine);	// Check with GJK 
	}

	glm::mat4 ConvexShapeCollider::GetModelMatrix() const
	{
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), transform.GetPosition());
		glm::mat4 rotateMatrix = glm::toMat4(transform.GetOrientation());
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), transform.GetScale());

		// ISROT
		glm::mat4 result = translateMatrix * rotateMatrix * scaleMatrix;
		return result;
	}

	std::vector<glm::vec3*> ConvexShapeCollider::GetVertices() const
	{
		// TBD: THIS IS REALLY UGLY 
		// Get the vertices of the convex shape with change in position and orientation
		std::vector<glm::vec3*> vertex;
		for (auto iter = vertices.begin(); iter != vertices.end(); ++iter)
		{
			glm::vec4 vec = glm::vec4(*(*iter), 1) * GetModelMatrix();
			vertex.push_back(new glm::vec3(vec.x, vec.y, vec.z));
		}

		return vertex;
	}
}
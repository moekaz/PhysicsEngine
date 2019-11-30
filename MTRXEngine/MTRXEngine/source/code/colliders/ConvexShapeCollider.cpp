#include <PrecompiledHeader.h>
#include <colliders/ConvexShapeCollider.h>

namespace mtrx
{
	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) : 
		ConvexShapeCollider(colliderType, Transform(center, orientation, scale))
	{}

	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const Transform& transform) : 
		Collider(colliderType, transform, true), transformModified(true)
	{}

	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const std::vector<glm::vec3*>& vertices, const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) :
		ConvexShapeCollider(colliderType, vertices, Transform(center, orientation,scale))
	{}

	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const std::vector<glm::vec3*>& vertices, const Transform& transform) :
		Collider(colliderType, transform, true), transformModified(true), vertices(vertices)
	{
		transformedVertices.resize(vertices.size());
  		for (int i = 0; i < vertices.size(); ++i)
		{
			transformedVertices[i] = new glm::vec3();
		}
	}

	ConvexShapeCollider::~ConvexShapeCollider()
	{
		for (int i = 0; i < vertices.size(); ++i)
		{
			delete vertices[i];
			delete transformedVertices[i];
		}
	}

	bool ConvexShapeCollider::RaycastCollision(const Ray& ray)
	{
		// A ray is a convex shape if we use it as a line segment
		glm::vec3 rayEndPoint = glm::fastNormalize(ray.direction) * MAX_RAY_SIZE;	// Get the end point of the ray

		std::array<glm::vec3*, 2> verts1 = { const_cast<glm::vec3*>(&ray.startPosition), &rayEndPoint };
		auto verts2 = GetVertices();

		return CollisionUtil::ConvexShapeCollision(verts1.begin(), verts1.end(), verts2->begin(), verts2->end());
	}

	glm::mat4 ConvexShapeCollider::GetModelMatrix() const
	{
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), GetPosition());
		glm::mat4 rotateMatrix = glm::toMat4(GetOrientation());
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), GetScale());

		// ISROT
		return translateMatrix * rotateMatrix * scaleMatrix;
	}

	std::vector<glm::vec3*>* ConvexShapeCollider::GetVertices() const
	{
		// If the collider was not modified no need to redo transform operation
		if (!transformModified)
			return &transformedVertices;

		glm::mat4 modelMatrix = GetModelMatrix();
		for (int i = 0; i < vertices.size(); ++i)
		{
			glm::vec4 vec = modelMatrix * glm::vec4(*vertices[i], 1.f);
			transformedVertices[i]->x = vec.x;
			transformedVertices[i]->y = vec.y;
			transformedVertices[i]->z = vec.z;
		}

		transformModified = false;
		return &transformedVertices;
	}
}
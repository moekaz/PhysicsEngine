#include <PrecompiledHeader.h>
#include <colliders/CapsuleCollider.h>

namespace mtrx
{
	// TBD: This will not work need to factor in orientation and scale of the capsule (need to fix this pretty quick)
	CapsuleCollider::CapsuleCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale, float radii, float height) :
		CapsuleCollider(Transform(center, orientation, scale), radii, height)
	{}

	CapsuleCollider::CapsuleCollider(const Transform& transform, float radii, float height) :
		Collider(ColliderType::Capsule, transform), height(height), radii(radii), A(GetPosition() - GetUp() * (height / 2)),
		B(GetPosition() - GetUp() * (height / 2))
	{}
}
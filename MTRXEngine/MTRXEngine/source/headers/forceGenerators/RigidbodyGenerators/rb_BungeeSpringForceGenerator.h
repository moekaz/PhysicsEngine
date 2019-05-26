#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_AnchoredSpringForceGenerator.h>

namespace MTRX
{
	class rb_BungeeSpringForceGenerator : public rb_AnchoredSpringForceGenerator
	{
	public:
		rb_BungeeSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength);
		~rb_BungeeSpringForceGenerator();

		virtual void UpdateForces(Rigidbody* rb) override;
	};
}

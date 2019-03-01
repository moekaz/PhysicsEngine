#pragma once

#include <entities/Particle.h>
#include <forceGenerators/AnchoredSpringForceGenerator.h>

namespace MTRX
{
	class BungeeSpringForceGenerator : public AnchoredSpringForceGenerator
	{
	public:
		virtual void UpdateForces(Particle* particle);

		BungeeSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength);
		~BungeeSpringForceGenerator();
	};
}

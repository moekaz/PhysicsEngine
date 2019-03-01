/*
	Author: Mohamed Kazma
	Description: A spring force generator that uses anchor points to generate the forces
	This can either be the center of a particle or just some fixed anchor its the same calculation
*/

#pragma once

#include <entities/Particle.h>
#include <forceGenerators/IForceGenerator.h>
#include <Defs.h>

namespace MTRX
{
	class AnchoredSpringForceGenerator : public IForceGenerator
	{
	public:
		glm::vec3* anchorPoint;
		SpringData spring;

		virtual void UpdateForces(Particle* particle);

		AnchoredSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength);
		~AnchoredSpringForceGenerator();

		inline void SetAnchorPoint(glm::vec3* point) { anchorPoint = point; }
	};
}


/*
	Author: Mohamed Kazma
	Description: Basic spring force generator implementation that will use hooke's law
	PS: The generator requires 2 particles the particle that the force is going to be applied to
	and the second that is on the other side of the spring that will be used to calculate this force 
	This force can probably be cached to be used later on but...
*/
#pragma once

#include <Particle.h>
#include <IForceGenerator.h>
#include <Defs.h>

namespace MTRX
{
	class DefaultSpringForceGenerator : public IForceGenerator
	{
	public:
		Particle* secondParticle; // The second particle on the other side of the spring
		SpringData spring; // The information that the spring will hold

		// Implementation of the forces that are generated by the spring 
		virtual void UpdateForces(Particle* particle);

		DefaultSpringForceGenerator(Particle* secondParticle, float stiffness, float restLength);
		~DefaultSpringForceGenerator();
	};
}

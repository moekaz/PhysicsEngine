/*
	Author: Mohamed Kazma
	Description: A gravity force generator that allows us to simulate gravitational forces on a particle 
*/
#pragma once

#include <Particle.h>
#include <IForceGenerator.h>

namespace MTRX
{
	class GravityForceGenerator : public IForceGenerator
	{
	public:
		glm::vec3 gravitationalAcceleration; // Gravitational acceleration

		// Implementation of an update forces for a force generator will apply a gravitational force on the particle
		virtual void UpdateForces(Particle* particle); 

		GravityForceGenerator(const glm::vec3& gravity);
		~GravityForceGenerator();
	};
}


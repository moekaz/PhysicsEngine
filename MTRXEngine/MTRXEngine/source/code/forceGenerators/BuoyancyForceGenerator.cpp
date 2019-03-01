#include "PrecompiledHeader.h"
#include "forceGenerators/BuoyancyForceGenerator.h"

namespace MTRX
{
 	BuoyancyForceGenerator::BuoyancyForceGenerator(float density, float volume, float maxPaticleDepth) : liquidProperties(density, volume),
		maxParticleDepth(maxPaticleDepth)
	{}

	BuoyancyForceGenerator::~BuoyancyForceGenerator()
	{}

	void BuoyancyForceGenerator::UpdateForces(Particle* particle)
	{
		// THE ASSUMPTION ATM IS THAT THE UP DIRECTION WE ARE USING IS THE Y AXIS AND THAT OUR LIQUID IS POSITIONED ACCORDINGLY 
		// IF WE WANT TO CHANGE THAT WE WOULD NEED A UP DIRECTION VECTOR


		// Check if even in liquid or in need of a force first
		float currentDepth = particle->GetPosition().y;
		if (currentDepth >= liquidHeight + maxParticleDepth)
			return;

		// Apply some buoyancy force
		glm::vec3 force;

		// Partially submerged object
		if (currentDepth > liquidHeight - maxParticleDepth)
			// NOT SURE ABT THIS PART
			force.y = liquidProperties.density * liquidProperties.volume * (liquidHeight + maxParticleDepth - currentDepth) / (2 * maxParticleDepth);
		else // Completely submerged object
			force.y = liquidProperties.density * liquidProperties.volume;

		// Don't we need to multiply that force by gravity??
		//force.y *= g;

		// Add the resulting force on the particle
		particle->AddForce(force);
	}
}
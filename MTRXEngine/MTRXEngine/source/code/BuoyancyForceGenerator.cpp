#include "PrecompiledHeader.h"
#include "BuoyancyForceGenerator.h"

namespace MTRX
{
 	BuoyancyForceGenerator::BuoyancyForceGenerator(float density, float volume, float depth, float paticleDepth) : liquidProperties(density, volume, depth), 
		particleDepth(particleDepth)
	{}

	BuoyancyForceGenerator::~BuoyancyForceGenerator()
	{}

	void BuoyancyForceGenerator::UpdateForces(Particle* particle)
	{
		// THE ASSUMPTION ATM IS THAT THE UP DIRECTION WE ARE USING IS THE Y AXIS AND THAT OUR LIQUID IS POSITIONED ACCORDINGLY 
		// IF WE WANT TO CHANGE THAT WE WOULD NEED A UP DIRECTION VECTOR

		// Depth of the particle 
		float currentDepth = particle->GetPosition().y;
		glm::vec3 force;

		// Partially submerged object
		if (currentDepth > liquidHeight - particleDepth)
			force.y = liquidProperties.density * liquidProperties.volume * (currentDepth - liquidProperties.depth - liquidHeight) / 2 * liquidProperties.depth;
		else // Completely submerged object
			force.y = liquidProperties.density * liquidProperties.volume;

		// Add the resulting force on the particle
		particle->AddForce(force);
	}
}
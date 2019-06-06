#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h"

namespace mtrx
{
	rb_BuoyancyForceGenerator::rb_BuoyancyForceGenerator(float volume, float maxPaticleDepth, float liquidHeight, float density) : liquidProperties(density, volume),
		maxParticleDepth(maxPaticleDepth), liquidHeight(0)
	{}

	rb_BuoyancyForceGenerator::~rb_BuoyancyForceGenerator()
	{}

	void rb_BuoyancyForceGenerator::UpdateForces(Rigidbody* rb)
	{
		// This is wrong now change this 

		// THE ASSUMPTION ATM IS THAT THE UP DIRECTION WE ARE USING IS THE Y AXIS AND THAT OUR LIQUID IS POSITIONED ACCORDINGLY 
		// IF WE WANT TO CHANGE THAT WE WOULD NEED A NEW UP DIRECTION VECTOR

		// Check if even in liquid or in need of a force first
		float currentDepth = rb->GetPosition().y;
		if (currentDepth >= liquidHeight + maxParticleDepth)
			return;

		// Apply some buoyancy force
		glm::vec3 force = glm::vec3();

		if (currentDepth <= liquidHeight - maxParticleDepth)
		{
			force.y = liquidProperties.density * liquidProperties.volume;
		}
		else
		{
			force.y = liquidProperties.density * liquidProperties.volume * (currentDepth - maxParticleDepth - liquidHeight) / (2 * maxParticleDepth);
		}
		//if (currentDepth > liquidHeight - maxParticleDepth) // Partially submerged object 
		//	force.y = liquidProperties.density * liquidProperties.volume * (liquidHeight + maxParticleDepth - currentDepth) / (2 * maxParticleDepth);
		//else // Completely submerged object
		//	force.y = liquidProperties.density * liquidProperties.volume;

		// Don't we need to multiply that force by gravity??
		//force.y *= gravity;

		// Add the resulting force on the particle
		rb->AddForce(force * 0.1f);
	}
}
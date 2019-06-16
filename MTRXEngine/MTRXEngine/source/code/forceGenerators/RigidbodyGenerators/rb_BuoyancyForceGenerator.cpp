#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h"

namespace mtrx
{
	rb_BuoyancyForceGenerator::rb_BuoyancyForceGenerator(float volumeDisplaced, float maxPaticleDepth, float liquidHeight, float density) : 
		volumeDisplaced(volumeDisplaced), maxParticleDepth(maxParticleDepth), liquidLevel(liquidHeight), liquidDensity(density)
	{}

	rb_BuoyancyForceGenerator::~rb_BuoyancyForceGenerator()
	{}

	void rb_BuoyancyForceGenerator::UpdateForces(Rigidbody* rb)
	{
		// This is wrong now change this 

		// Check if even in liquid or in need of a force first
		float currentDepth = rb->GetPosition().y;
		//if (currentDepth >= liquidLevel + maxParticleDepth)
			//return;
		if (currentDepth >= liquidLevel)
			return;

		// Apply some buoyancy force
		glm::vec3 force = glm::vec3(0.f, liquidDensity * volumeDisplaced * gravity, 0.f);
		float submergenceRatio;
		if (currentDepth <= liquidLevel - maxParticleDepth)
		{
			submergenceRatio = 2.f;
			std::cout << "completely submerged" << std::endl;
		}
		else
		{
			submergenceRatio = 1.f + (liquidLevel - currentDepth) / (liquidLevel - maxParticleDepth);
			std::cout << "partially submerged" << std::endl;
		}
		
		force.y *= submergenceRatio;

		// Add the resulting force on the particle
		rb->AddForce(force);
	}
}
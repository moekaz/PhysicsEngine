#include "PrecompiledHeader.h"
#include "forceGenerators/GravityForceGenerator.h"

namespace MTRX
{
	GravityForceGenerator::GravityForceGenerator(const glm::vec3& gravity) : gravitationalAcceleration(gravity)
	{}

	GravityForceGenerator::~GravityForceGenerator()
	{}

	void GravityForceGenerator::UpdateForces(Particle* particle)
	{
		// Check for infinite mass
		if (particle->isInfiniteMass())
			return;
		
		// Add gravitational force to the particle according to f = ma
		particle->AddForce(gravitationalAcceleration * particle->GetMass()); 
	}
}
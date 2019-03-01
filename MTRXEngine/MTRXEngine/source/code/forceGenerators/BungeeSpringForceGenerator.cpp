#include "PrecompiledHeader.h"
#include "forceGenerators/BungeeSpringForceGenerator.h"


namespace MTRX
{
	BungeeSpringForceGenerator::BungeeSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength) : 
		AnchoredSpringForceGenerator(anchorPoint, stiffness, restLength)
	{}

	BungeeSpringForceGenerator::~BungeeSpringForceGenerator()
	{}

	void BungeeSpringForceGenerator::UpdateForces(Particle* particle)
	{
		// Get the difference in position between the 2 particles on either side of the spring
		glm::vec3 generatedForce = particle->GetPosition() - *anchorPoint;
		float mag = glm::length(generatedForce);

		// Check that the spring is extended since no force will be generated unless it is
		if (mag <= spring.restLength)
			return;

		// Apply Hooke's law
		mag = spring.stiffness * abs(mag - spring.restLength);

		glm::normalize(generatedForce);
		generatedForce *= -mag;
		particle->AddForce(generatedForce);
	}
}
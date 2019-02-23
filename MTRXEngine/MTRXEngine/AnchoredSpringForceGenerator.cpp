#include "PrecompiledHeader.h"
#include "AnchoredSpringForceGenerator.h"

namespace MTRX
{
	AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength) : anchorPoint(anchorPoint), 
		spring(stiffness, restLength)
	{}

	AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
	{}

	void AnchoredSpringForceGenerator::UpdateForces(Particle* particle)
	{
		// Get the difference in position between the 2 particles on either side of the spring
		glm::vec3 generatedForce = particle->GetPosition() - *anchorPoint;
		float mag = glm::length(generatedForce);

		// Apply Hooke's law
		mag = spring.stiffness * abs(mag - spring.restLength);

		glm::normalize(generatedForce);
		generatedForce *= -mag;
		particle->AddForce(generatedForce);
	}
}

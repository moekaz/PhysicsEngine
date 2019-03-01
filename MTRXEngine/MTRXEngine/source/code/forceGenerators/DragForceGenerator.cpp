#include <PrecompiledHeader.h>
#include "forceGenerators/DragForceGenerator.h"

namespace MTRX
{
	DragForceGenerator::DragForceGenerator(float k1, float k2) : k1(k1), k2(k2)
	{}

	DragForceGenerator::~DragForceGenerator()
	{}

	void DragForceGenerator::UpdateForces(Particle& particle)
	{
		// Check for infinite mass
		if (particle.isInfiniteMass())
			return;
		
		// MIGHT NEED SOME OPTIMIZATION FOR SQRT CALLS??
		glm::vec3& velocity = particle.GetVelocity();
		float dragScalar = glm::length(particle.GetVelocity());
		dragScalar = k1 * dragScalar + k2 * dragScalar * dragScalar; // Calculate drag coefficient
		
		glm::vec3 dragForce = glm::normalize(velocity); // Get the direction vector of the velocity so that drag is against it
		dragForce *= -dragScalar;

		particle.AddForce(dragForce);
	}
}

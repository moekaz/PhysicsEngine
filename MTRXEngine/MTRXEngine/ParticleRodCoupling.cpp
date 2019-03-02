#include "PrecompiledHeader.h"
#include "ParticleRodCoupling.h"

namespace MTRX
{
	ParticleRodCoupling::ParticleRodCoupling(float length) : length(length)
	{}

	ParticleRodCoupling::~ParticleRodCoupling()
	{}

	void ParticleRodCoupling::GenerateContact(ParticleCollision& collision)
	{
		// THIS SHOULD GENERATE 2 CONTACT AS TO NOT MAKE THE ROD VIBRATE

		// Check the length of the rod
		float currentLengthSqr = GetCurrentLengthSqr();
		if (currentLengthSqr == lengthSqr)
			return;

		// Calculate the collision normal
		glm::vec3 normal = glm::normalize(particles[1]->GetPosition() - particles[0]->GetPosition());

		// Check which direction we need to generate the particle contact collision
		if (currentLengthSqr > lengthSqr)
		{
			collision = ParticleCollision(particles[0], particles[1], 0, normal);
			collision.penetration = sqrt(currentLengthSqr - lengthSqr);
		}
		else
		{
			normal = -normal;
			collision = ParticleCollision(particles[0], particles[1], 0, normal);
			collision.penetration = sqrt(lengthSqr - currentLengthSqr);
		}
	}
}
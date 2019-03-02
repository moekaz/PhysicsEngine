#include "PrecompiledHeader.h"
#include "ParticleCableCoupling.h"

namespace MTRX
{
	ParticleCableCoupling::ParticleCableCoupling(float maxLengthSqr, float restitution) : maxLengthSqr(maxLengthSqr), restitution(restitution)
	{}

	ParticleCableCoupling::~ParticleCableCoupling()
	{}

	// THIS MIGHT NEED TO BE REDONE
	void ParticleCableCoupling::GenerateContact(ParticleCollision& collision)
	{
		// If the cable is not taut enough no contact will be generated
		float lengthSqr = GetCurrentLengthSqr();
		if (lengthSqr < maxLengthSqr)
			return;

		// Calculate collision normal
		glm::vec3 collisionNormal = glm::normalize(particles[1]->GetPosition() - particles[0]->GetPosition());

		// Create a new particle collision with these 2 particles
		collision = ParticleCollision(particles[0], particles[1], restitution, collisionNormal);
		collision.penetration = sqrt(lengthSqr - maxLengthSqr); // We need the actual lengths so we are gonna have to bite the bullet with sqrt
	}
}
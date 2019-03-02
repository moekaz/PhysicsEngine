#include "PrecompiledHeader.h"
#include "ParticleCableCoupling.h"

namespace MTRX
{
	ParticleCableCoupling::ParticleCableCoupling(float maxLengthSqr, float restitution) : maxLengthSqr(maxLengthSqr), restitution(restitution)
	{}

	ParticleCableCoupling::~ParticleCableCoupling()
	{}

	void ParticleCableCoupling::GenerateContact(ParticleCollision& collision)
	{
		// If the cable is not taut enough no contact will be generated
		float lengthSqr = GetCurrentLengthSqr();
		if (lengthSqr < maxLengthSqr)
			return;

		// Create a new particle collision with these 2 particles
		ParticleCollision collision = ParticleCollision(particles[0], particles[1], restitution, glm::normalize(particles[1]->GetPosition - particles[0]->GetPosition()));
		collision.penetration = sqrt(lengthSqr - maxLengthSqr); // We need the actual lengths so we are gonna have to bite the bullet with sqrt
	}
}
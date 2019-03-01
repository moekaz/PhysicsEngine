#include "PrecompiledHeader.h"
#include "ParticleCollision.h"

namespace MTRX
{
	// IF THE COLLISION IS BETWEEN A PARTICLE AND AN IMMOVABLE OBJECT PROVIDE YOUR NORMAL AS THIS WILL NOT WORK
	ParticleCollision::ParticleCollision(Particle* particle1, Particle* particle2, float restitution) : particles {particle1, particle2}, restitution(restitution),
		collisionNormal(glm::normalize(particles[0]->GetPosition() - particles[1]->GetPosition()))
	{}

	ParticleCollision::~ParticleCollision()
	{}

	float ParticleCollision::CalculateSeparatingVelocity() const
	{
		// Assuming that both particles exist if not then u have a problem
		glm::vec3 relVelocity = particles[0]->GetVelocity();
		relVelocity -= particles[1]->GetVelocity(); // Would be zero if the object is immovable
		return glm::dot(relVelocity, collisionNormal); // Dot product of the 2 vectors
	}

	void ParticleCollision::Resolve()
	{
		ResolveVelocity();
		ResolveInterpenetration();
	}

	void ParticleCollision::ResolveVelocity()
	{
		// Assuming that both particles exist in the array

		// Check if its already separating or stationary
		float seperatingVelocity = CalculateSeparatingVelocity();
		if (seperatingVelocity > 0)
			return;

		// Check if both have infinite mass if they do no impulse generated
		float totalInverseMass = particles[0]->GetInverseMass() + particles[1]->GetInverseMass();
		if (totalInverseMass <= 0)
			return;

		// Calculate the new separating velocity and factor in the restitution
		float newSeperatingVelocity = -seperatingVelocity * restitution;
		float deltaVelocity = newSeperatingVelocity - seperatingVelocity;
		float impulse = deltaVelocity / totalInverseMass;
		glm::vec3 impulsePerMass = collisionNormal * impulse;

		// Apply the impulses
		if (!particles[0]->isInfiniteMass())
		{
			particles[0]->GetVelocity() += impulsePerMass * particles[0]->GetInverseMass();
		}

		// Apply opposite impulse
		if (!particles[1]->isInfiniteMass())
		{
			particles[1]->GetVelocity() += impulsePerMass * -particles[1]->GetInverseMass();
		}
	}

	void ParticleCollision::ResolveInterpenetration() 
	{
		// Assuming that the 2 particles exist 

		// If there is no proper penetration
		if (penetration <= 0)
			return;

		// Check that both particles are not infinite mass
		float totalInverseMass = particles[0]->GetInverseMass() + particles[1]->GetInverseMass();
		if (totalInverseMass <= 0)
			return;

		// Find the movement vector according to penetration and inverse mass
		glm::vec3 moveVector = collisionNormal * (-penetration / totalInverseMass);

		// Apply this movement vector
		if (particles[0]->GetInverseMass())
		{
			particles[0]->GetPosition() += moveVector * particles[0]->GetInverseMass();
		}

		if (particles[1]->GetInverseMass())
		{
			particles[1]->GetPosition() += moveVector * -particles[1]->GetInverseMass();
		}
	}
}

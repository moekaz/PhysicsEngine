#include <PrecompiledHeader.h>
#include <Particle.h>

namespace MTRX
{
	Particle::Particle(const glm::vec3& position, const float inverseMass) : position(position), velocity(glm::vec3()), acceleration(glm::vec3()), 
		inverseMass(inverseMass), accumForces(glm::vec3()), forceRegistry(ForceGenerationRegistry(this))
	{}

	Particle::~Particle()
	{}

	void Particle::PhysicsUpdate()
	{
		// If we have an inverseMass of 0 we should not be updating
		if (inverseMass <= 0)
			return;

		// Update the forces that we are generating before calculating the acceleration
		forceRegistry.UpdateForceGenerators();

		// Update acceleration using newton's second law
		acceleration = accumForces * inverseMass;

		// If we use a damping force generator we can set damping to somewhere around 1
		// Update the velocity of the particle using its acceleration and add some damping (maybe use pow on the drag it is much slower)
		//velocity = velocity * pow(damping, GameTime::deltaTime) + acceleration * GameTime::deltaTime;
		velocity = velocity * damping + acceleration * GameTime::deltaTime;

		// Update the position of the particle using its velocity and acceleration (acceleration is not necessary)
		//position += velocity * GameTime::deltaTime + acceleration * GameTime::deltaTime * GameTime::deltaTime * 0.5f;
		position += velocity * GameTime::deltaTime;
		
		// Reset accumulated forces
		accumForces.x = 0;
		accumForces.y = 0;
		accumForces.z = 0;
	}

	void Particle::AddForce(const glm::vec3& force)
	{
		accumForces += force;
	}

	void Particle::SetMass(const float mass) 
	{
		assert(mass != 0); // We are not supposed to have a 0 mass 
		inverseMass = 1.f / mass; 
	}

	float Particle::GetMass() const
	{
		if (inverseMass == 0)
			return MAX_MASS;
		else
			return 1.f / inverseMass;
	}
}
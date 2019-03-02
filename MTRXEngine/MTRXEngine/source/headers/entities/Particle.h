/*
	Author: Mohamed Kazma
	Description: A basic particle mass that will have a position velocity and acceleration 
	without including anything complicated like orientation etc...
*/

#pragma once

#define MAX_MASS 10000000.f // Some large number i am going to use to simulate a very large mass

#include <IUpdateable.h>
#include <GameTime.h>

namespace MTRX
{
	class Particle : public IUpdateable
	{
	public:
		Particle(const glm::vec3& position = glm::vec3(), const float inverseMass = 0);
		~Particle();

		// Implementation of the physics engine update
		virtual void PhysicsUpdate() override;
		// Add forces
		void AddForce(const glm::vec3& force);
		// Checking if we have infinite mass
		inline bool isInfiniteMass() { return inverseMass == 0.f; }

		/* Setters */
		void SetMass(const float mass);
		inline void SetInverseMass(const float inverseMass) { this->inverseMass = inverseMass; }
		inline void SetPosition(const glm::vec3& position) { this->position = position; }
		inline void SetVelocity(const glm::vec3& velocity) { this->velocity = velocity; }
		inline void SetAcceleration(const glm::vec3& acceleration) { this->acceleration = acceleration; }
		inline void SetDamping(const float damping) { this->damping = damping; }

		/* Getters */
		float GetMass() const;
		inline float GetInverseMass() const { return inverseMass; }
		inline float GetDamping() const { return damping; }
		inline glm::vec3& GetPosition() { return position; }
		inline glm::vec3& GetVelocity() { return velocity; }
		inline glm::vec3& GetAcceleration() { return acceleration; }

		friend std::ostream& operator<<(const std::ostream& os, const Particle& particle); // Some way of printing out a particle
	protected:
		glm::vec3 position; // Position of the particle in space 
		glm::vec3 velocity; // Velocity of this particle 
		glm::vec3 acceleration; // Acceleration of this particle
		glm::vec3 accumForces; // Accumulated forces 
		float damping; // Simple damping for frictional forces (between 0 and 1)
		float inverseMass; // The mass of the particle (inverse mass is better as we don't want a zero mass and having a value of 0 is easy but infinity is hard)
	};
}
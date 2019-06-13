
#pragma once

#include <IUpdateable.h>
#include <Defs.h>

namespace mtrx
{
	#define MAX_MASS 10000000.f // Some large number 

	class Body : IUpdateable
	{
	public:
		Body(const glm::vec3& position = glm::vec3(), const glm::quat& orientation = glm::quat(), const glm::vec3& scale = glm::vec3(), const float inverseMass = 0);
		~Body();

		// Add forces
		inline void AddForce(const glm::vec3& force) { accumForces += force; }
		// Implementation of the physics engine update
		virtual void PhysicsUpdate() = 0;
		// Clear all the accumulators
		virtual void ClearAccumulators() = 0;

		// Setters 
		inline void SetInverseMass(const float inverseMass) { this->inverseMass = inverseMass; }
		inline void SetPosition(const glm::vec3& position) { this->transform.position = position; }
		inline void SetVelocity(const glm::vec3& velocity) { this->velocity = velocity; }
		inline void SetAcceleration(const glm::vec3& acceleration) { this->acceleration = acceleration; }
		inline void SetDamping(const float damping) { this->linearDamping = damping; }
		void SetMass(const float mass);

		// Getters
		inline glm::quat& GetOrientation() { return transform.orientation; }
		inline bool GetIsInfiniteMass() { return inverseMass == 0.f; }
		inline float GetInverseMass() const { return inverseMass; }
		inline float GetDamping() const { return linearDamping; }
		inline glm::vec3& GetPosition() { return transform.position; }
		inline glm::vec3& GetVelocity() { return velocity; }
		inline glm::vec3& GetAcceleration() { return acceleration; }
		inline glm::vec3& GetAccumForces() { return accumForces; }
		inline Transform* GetTransform() { return &transform; }
		float GetMass() const;

	protected:
		Transform transform; // Transform information
		//glm::vec3 position; // Position of the particle in space 
		glm::vec3 velocity; // Velocity of this particle 
		glm::vec3 acceleration; // Acceleration of this particle
		glm::vec3 accumForces; // Accumulated forces 
		float linearDamping; // Simple damping for frictional forces (between 0 and 1)
		float inverseMass; // The mass of the particle (inverse mass is better as we don't want a zero mass and having a value of 0 is easy but infinity is hard)
	};
}

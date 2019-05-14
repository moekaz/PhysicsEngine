/*
	Author: Mohamed Kazma
	Description: Implementation of rigidbodies
*/

#include <PrecompiledHeader.h>
#include <entities/Rigidbody.h>

namespace MTRX
{
	// Constructor
	Rigidbody::Rigidbody(float mass, bool isKinematic, const glm::vec3& position) : Body(position, mass), isKinematic(isKinematic), 
		orientation(glm::quat()), forward(glm::vec3(0, 0, -1)), side(glm::vec3(1, 0, 0)), up(glm::vec3(0, 1, 0))
	{}

	// Destructor
	Rigidbody::~Rigidbody() {}

	// Update the values of the rigid body
	void Rigidbody::PhysicsUpdate()
	{
		// Do not perform physics calculations
		if (isKinematic || GetIsInfiniteMass())
			return;

		// Get acceleration with accumulated forces and inverse mass
		prevAcceleration = acceleration + inverseMass * accumForces;
		
		// Get angular acceleration
		glm::vec3 angularAcceleration = accumTorque * CalculateIITWorld();

		// Integrate the acceleration to get the velocity
		velocity += prevAcceleration * GameTime::deltaTime;

		// Integrate the angular acceleration to get the rotation
		rotation += angularAcceleration * GameTime::deltaTime;

		// Drag linear and rotation
		velocity += std::pow(linearDamping, GameTime::deltaTime);
		rotation *= std::pow(angularDamping, GameTime::deltaTime);

		// Update rotation and position
		position += velocity * GameTime::deltaTime;
		orientation *= rotation * GameTime::deltaTime;

		// Calculate the body data from the updated positions
		CalculateBodyData();
		
		// Clear the accumulators
		ClearAccumulators();

		// Sleep stuff if needed
	}

	void Rigidbody::ClearAccumulators()
	{
		accumTorque.x = 0;
		accumTorque.y = 0;
		accumTorque.z = 0;
		accumForces.x = 0;
		accumForces.y = 0;
		accumForces.z = 0;
	}

	void Rigidbody::IntegrateRotation()
	{}

	void Rigidbody::AddForceAtPoint(glm::vec3& force, glm::vec3& point)
	{
		// Convert to coordinates relative to center of mass.
		glm::vec3 pt = point;
		pt -= position;

		accumForces += force;
		accumTorque += pt % force;
	}

	void Rigidbody::CalculateBodyData()
	{
		// Normalize orientation
		glm::normalize(orientation);

		// Calculate the object to world transform
		CalculateObjToWorldMat();
		
		// Calculate inverse inertia tensor in world coordinates
		CalculateIITWorld();
	}
	
	void Rigidbody::CalculateObjToWorldMat()
	{
		// i,j,k -> x,y,z
		objToWorldMat[0][0] = 1 - 2 * orientation.y * orientation.y - 2 * orientation.z * orientation.z;
		objToWorldMat[0][1] = 2 * orientation.x * orientation.y - 2 * orientation.w * orientation.z;
		objToWorldMat[0][2] = 2 * orientation.x * orientation.z + 2 * orientation.w * orientation.y;
		objToWorldMat[0][3] = position.x;
		objToWorldMat[1][0] = 2 * orientation.x * orientation.y + 2 * orientation.w * orientation.z;
		objToWorldMat[1][1] = 1 - 2 * orientation.x * orientation.x - 2 * orientation.z * orientation.z;
		objToWorldMat[1][2] = 2 * orientation.y * orientation.z - 2 * orientation.w * orientation.x;
		objToWorldMat[1][3] = position.y;
		objToWorldMat[2][0] = 2 * orientation.x * orientation.z - 2 * orientation.w * orientation.y;
		objToWorldMat[2][1] = 2 * orientation.y * orientation.z + 2 * orientation.w * orientation.x;
		objToWorldMat[2][2] = 1 - 2 * orientation.x * orientation.x - 2 * orientation.y * orientation.y;
		objToWorldMat[2][3] = position.z;
	}
}
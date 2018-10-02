/*
	Author: Mohamed Kazma
	Description: Implementation of rigidbodies
*/

#include "../headers/Rigidbody.h"

// MIGHT WANT TO READ UP ON SOME TORQUE AND ROTATIONAL FORCES

// Set the value of gravity that will be used for gravity calculations 
float Rigidbody::gravity = 9.81;

// Constructor
Rigidbody::Rigidbody(float mass, bool isKinematic, const glm::vec3& position, float maxSpeed)
{
	this->mass = mass;
	this->isKinematic = isKinematic;
	this->position = position;
	this->maxSpeed = maxSpeed;
	velocity = glm::vec3();
	acceleration - glm::vec3();
	orientation = glm::quat();
	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	side = glm::vec3(1, 0, 0);
}

// Destructor
Rigidbody::~Rigidbody() {}

// Get Position 
glm::vec3& Rigidbody::GetPosition() { return position; }

// Set position
void Rigidbody::SetPosition(const glm::vec3& position) { this->position = position; }

// Update the values of the rigid body
void Rigidbody::PhysicsUpdate()
{
	// Check for gravity 
	if (isKinematic) acceleration.y -= gravity;

	// A = V / T => V = A * T
	velocity = acceleration * GameTime::deltaTime;
	
	// Create a rotation from the position u r at to the new position we are at using the forward vector
	LookAt(position + velocity);

	// Move the position of the rigidbody
	position += velocity;

	// Reset the velocity values
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	
	// Reset acceleration values
	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;
}

// Apply a force on an rigidbody (Newtonian force application)
void Rigidbody::ApplyForce(const glm::vec3& force)
{
	acceleration += force / mass;	// Newtonian physics (SUM OF FORCES = MASS * ACCELERATION)
}

// Rotate a rigidbody with a certain rotation quaternion
void Rigidbody::Rotate(const glm::quat& rotation)
{
	orientation = rotation * orientation;
}

// Look at a certain position
void Rigidbody::LookAt(const glm::vec3& lookPosition)
{
}

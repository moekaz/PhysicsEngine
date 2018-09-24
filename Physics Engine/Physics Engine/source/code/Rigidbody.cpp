/*
	Author: Mohamed Kazma
	Description: Implementation of rigidbodies
*/

#include "../headers/Rigidbody.h"

// MIGHT WANT TO READ UP ON SOME TORQUE AND ROTATIONAL FORCES

// Set the value of gravity that will be used for gravity calculations 
static float gravity = 9.81;

// Constructor
Rigidbody::Rigidbody(float mass, bool isKinematic, const glm::vec3& position)
{
	this->mass = mass;
	this->isKinematic = isKinematic;
	this->position = position;
	velocity = glm::vec3();
	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	side = glm::vec3(1, 0, 0);
	orientation = glm::quat();
}

// Destructor
Rigidbody::~Rigidbody() {}

// Update the values of the rigid body
void Rigidbody::Update()
{
	// Check for gravity 
	if (isKinematic) velocity.y -= gravity;

	// Move the position of the rigidbody with some delta time multiplication
	position += velocity * GameTime::deltaTime;

	// Reset the velocity values
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
}

// Apply a force on an rigidbody (Newtonian force application)
void Rigidbody::ApplyForce(glm::vec3& force)
{
	velocity += force;
}

// Move a rigid body to a certain position
void Rigidbody::Move(glm::vec3& vel)
{
	velocity += vel;
}

// Rotate a rigidbody with a certain rotation quaternion
void Rigidbody::Rotate(glm::quat& rotation)
{
	orientation = rotation * orientation;
}

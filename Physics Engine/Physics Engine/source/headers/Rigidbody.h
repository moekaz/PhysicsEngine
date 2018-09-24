/*
	Author: Mohamed Kazma
	Description: Rigidbody physics implementation
*/

#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "Collider.h"
#include "GameTime.h"

class Rigidbody
{
public:
	static float gravity;	// The value of gravity for the world
	float mass;	// Mass of the rigid body
	float airResistance;	// The value of drag
	float angularDrag;	// Angular drag
	bool isKinematic;	// Check for whether the body is on the floor or not 
	Collider* collider;	// Current collider that we are using (DO WE WANT AN ARRAY OF THEM JUST IN CASE???)
	glm::vec3 position;	// Position of the rigidbody
	glm::vec3 velocity; // Velocity of the rigidbody
	glm::vec3 forward;	// forward vector
	glm::vec3 side;	// Side vector
	glm::vec3 up;	// Up vector
	glm::quat orientation;	// The orientation of a rigidbody

	Rigidbody(float mass = 1.f, bool iskinematic = true, const glm::vec3& position = glm::vec3());	// Constructor
	~Rigidbody();	// Destructor
	
	void Update();	// Update the values of the rigidbody
	void ApplyForce(glm::vec3& force);	// Apply a force on a rigidbody
	void Move(glm::vec3& velocity);	// Add a certain amount of velocity
	void Rotate(glm::quat& rotation);	// rotate the rigidbody

private:
protected:
};
#endif // !RIGIDBODY_H

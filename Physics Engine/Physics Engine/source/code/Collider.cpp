/*
	Author: Mohamed Kazma
	Description: Some general implementation of all colliders
*/

#include "../headers/Collider.h"

static int id = 0;

/* Constructor */
Collider::Collider(const glm::vec3& vec)
{	
	++id;
	colliderId = id;															// Collider id for map hashing
	enabled = true;																// Is the collider turned on 
	trigger = false;															// Is it a trigger collider
	isColliding = false;														// Is colliding with another collider
	exitedCollision = false;													// Left Collision
	enteredCollision = false;													// Just entered collision
	stillColliding = false;														// still in collision
	center = vec;																// Position of the center of the collider
	forwardDirection = glm::vec3(0, 0, -1);										// Forward direction
	upDirection = glm::vec3(0, 1, 0);											// Up vector
	sideDirection = glm::normalize(glm::cross(-forwardDirection, upDirection));	// Calculate directions of the collider
}

/* Destructor */
Collider::~Collider() 
{
	// Delete the vertices
	for (int i = 0; i < vertices.size(); ++i)
	{
		delete vertices[i];
	}
}

/* Functions */

// Update collision info 
void Collider::UpdateCollisionInfo()
{
	// Do some checks on what is the state of the collision
	if (isColliding)
	{
		if (enteredCollision)
		{
			enteredCollision = false;	// Entering collision only happens on one frame
			stillColliding = true;		// Still in collision
		}
		else if (!stillColliding)
		{
			enteredCollision = true;
		}
	}
	else
	{
		if (exitedCollision) exitedCollision = false;	// exiting collision only occurs once
		else if (stillColliding || enteredCollision) exitedCollision = true;

		// reset the values
		enteredCollision = false;
		stillColliding = false;
	}
}

// Checking for whether we just entered collision
bool Collider::CollisionEnter()
{
	return false;
}

// Checking for whether we just exited collision
bool Collider::CollisionExit()
{
	return false;
}

// Checking for whether we are staying in collision
bool Collider::CollisionStay()
{
	return false;
}

// Print the general values of a collider
std::ostream& operator<<(std::ostream& os , const Collider& col)
{
	os << "Collider:" << std::endl
		<< "---------" << std::endl
		<< "Center: " << std::endl 
		<< "x: " << col.center.x << std::endl
		<< "y: " << col.center.y << std::endl
		<< "z: " << col.center.z;
	 
	return os;
}

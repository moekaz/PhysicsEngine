/*
	Author: Mohamed Kazma
	Description: Some general implementation of all colliders
*/

#include "../headers/Collider.h"

#include <iostream>

/* Constructor */
Collider::Collider(Vector3D vec)
{	
	enabled = true;					// Is the collider turned on 
	trigger = false;				// Is it a trigger collider
	isColliding = false;			// Is colliding with another collider
	exitedCollision = false;		// Left Collision
	enteredCollision = false;		// Just entered collision
	stillColliding = false;			// still in collision
	center = vec;					// Position of the center of the collider
}

/* Destructor */
Collider::~Collider() {}

/* Functions */

// Collision detection checks for colliders
bool Collider::CheckCollision(Collider& col)
{
	switch (col.type) 
	{
		case ColliderType::Sphere: 
		{
			std::cout << "checking collision with sphere" << std::endl;	// Check collision with sphere (use static casts unfortunately)
			isColliding = SphereCollision(col);
		}
		case ColliderType::Box:
		{
			std::cout << "checking collision with box collider" << std::endl;
			isColliding = BoxCollision(col);
		}
		case ColliderType::Capsule:
		{
			std::cout << "checking collision with capsule collider" << std::endl;
			isColliding = CapsuleCollision(col);
		}
		case ColliderType::Mesh:
		{
			std::cout << "checking collision with a mesh collider" << std::endl;
			isColliding = CapsuleCollision(col);
		}
		default: 
		{
			// If shit hits the fan
			std::cout << "Houston we have a problem" << std::endl;
		}
	}

	return isColliding;
}

// Checking for whether we just entered collision
bool Collider::CollisionEnter()
{
}

// Checking for whether we just exited collision
bool Collider::CollisionExit()
{
}

// Checking for whether we are staying in collision
bool Collider::CollisionStay()
{
}


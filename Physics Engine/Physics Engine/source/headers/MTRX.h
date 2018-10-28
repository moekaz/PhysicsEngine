/*
	Author: Mohamed Kazma
	Description: This should be the main physics engine file that will implement what is needed by the engine
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm/vec3.hpp>

#include "IUpdateable.h"
#include "Collider.h"
#include "Mat3.h"

class MTRX : public IUpdateable
{
public:
	std::map<int , Collider> collider;		// Store the colliders that we want to run through

	MTRX();								// Constructor
	~MTRX();							// Destructor

	void PhysicsUpdate();				// Update the game engine values
	void NarrowPhase();					// Narrow phase collision detection checks
	void BroadPhase();					// Broad phase collision detection checks

	Collider* Raycast();				// Raycast without any filtering of colliders
	Collider* RaycastFiltered();		// Raycast with filtering out some colliders
private:
protected:
};
/*
	Author: Mohamed Kazma
	Description: 
*/

#pragma once

#include <glm/vec3.hpp>

class Simplex
{
public:
	glm::vec3 b, c, d;	// Points generally get added to the simplex in alphabetical order the point a is always the newest point which will then become b or be removed
	int size;			// The size of the simplex this will be at most 4 (a, b, c, d)

	Simplex();			// Constructor
	~Simplex();			// Destructor
};
/*
	Author: Mohamed Kazma
	Description: Implementation of a ray
*/

#include "../headers/PrecompiledHeader.h"
#include "../headers/Ray.h"

namespace MTRX
{
	// Constructor
	Ray::Ray(const glm::vec3& startPos, const glm::vec3& rayDirection) : startPosition(startPos), direction(rayDirection) {}

	// Destructor
	Ray::~Ray() {}
}
/*
	Author: Mohamed Kazma
	Description: Implementation of a ray
*/

#include <PrecompiledHeader.h>
#include <Ray.h>

namespace mtrx
{
	// Constructor
	Ray::Ray(const glm::vec3& startPos, const glm::vec3& rayDirection) : startPosition(startPos), direction(rayDirection) {}

	// Destructor
	Ray::~Ray() {}
}
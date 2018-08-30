/*
	Author: Mohamed Kazma
	Description: A ray that will be used for raycasting
*/

#pragma once
#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

class Ray
{
public:
	Ray(const glm::vec3& startpos = glm::vec3(), const glm::vec3& rayDirection = glm::vec3());
	~Ray();

	glm::vec3 startPosition;	// The position where the ray starts at
	glm::vec3 direction;		// The direction the ray will go in

private:
protected:
};
#endif // !RAY_H
/*
	Author: Mohamed Kazma
	Description: Utility file that would include general functions that can be useful for general use
*/

#pragma once
#ifndef PHYSICSUTIL_H
#define PHYSICSUTIL_H
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <vector>
#include <map>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm\glm.hpp>
#include <glm/vec3.hpp>

#include "Ray.h"
#include "CollisionUtil.h"
#include "Collider.h"

namespace PhysicsUtil
{
	glm::vec3 TripleCross(glm::vec3& a, glm::vec3& b, glm::vec3& c);	// Calculates the triple cross product of 3 vectors
	float MinDistanceTwoLines(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);	// Minimum distance between 2 lines squared
	float MinDistanceSquaredTwoSegments(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);	// Minimum distance between 2 line segments squared
	float MinDistanceSquaredPointSegment(glm::vec3& , glm::vec3& , glm::vec3& , glm::vec3&);	// Minimum ditance between a point and a line segment squared
	float MinDistanceSquaredPointRay(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);	// Minimum distance between a point and a ray squared
	float MinDistanceSquaredLineSegmentRay(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);	// Minimum distance between a line segment and a ray squared
	Collider* RaycastFiltered(std::map<int, Collider*>& colliders, std::vector<Collider*>& filterColliders, glm::vec3& rayStartPosition, glm::vec3& rayDirection);	// Raycast check on colliders filtered
	Collider* RaycastUnfiltered(std::map<int, Collider*>& colliders, glm::vec3& rayStartPosition, glm::vec3& rayDirection);	// Raycast check for all colliders
	glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t);	// Linear interpolation of a rotation (Quaternions)
	glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t);	// Linear interpolation along a line segment
	float Ease(float t);	// Easing a float along a half sin curve to simulate acceleration
}
#endif // !PHYSICSUTIL_H
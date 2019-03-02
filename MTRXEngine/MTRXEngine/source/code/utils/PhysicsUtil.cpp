/*
	Author: Mohamed Kazma
	Description: This will be a util file that will include some functions that a physics engine will generally need
	Implementation of smallest distance between 2 line segments:
		http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment
*/

#include <PrecompiledHeader.h>
#include <utils/PhysicsUtil.h>

namespace MTRX
{
	namespace PhysicsUtil
	{
		// Optimizes 2 cross product calls into 2 dot product ones
		glm::vec3 TripleCross(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
		{
			// (A x B) x C = B(C . A) - A(C . B)
			return b * (glm::dot(c, a)) - a * (glm::dot(c, b));
		}

		// Finding the minimum distance between infinite lines
		float MinDistanceTwoLines(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
		{
			glm::vec3 l1 = B - A;	// First direction vector 
			glm::vec3 l2 = D - C;	// Second direction vector

			glm::vec3 normalPlane = glm::normalize(glm::cross(l1, l2));

			if (normalPlane == glm::vec3())
			{
				// They are parallel so choose any new vector that is not parallel to one of them and do the cross product for that it should be parallel to both
				glm::vec3 newVec = l2 + glm::vec3(1, 1, 1);
				normalPlane = glm::cross(l1, newVec);	// If the normal vector is (0,0,0) choose one of the 2 
			}

			return abs(glm::dot(C - A, normalPlane));
		}

		// Finding the minimum distance between 2 line segments
		float MinDistanceSquaredTwoSegments(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
		{
			glm::vec3 u = B - A;
			glm::vec3 v = D - C;
			glm::vec3 w = A - C;
			float a = glm::dot(u, u);
			float b = glm::dot(u, v);
			float c = glm::dot(v, v);
			float d = glm::dot(u, w);
			float e = glm::dot(v, w);
			float _D = a * c - b * b;
			float sc = 0, sn = 0;
			float sd = _D;
			float tc = 0, tn = 0;
			float td = _D;

			// Segments almost parallel
			if (_D < std::numeric_limits<float>::epsilon())
			{
				sn = 0.0f;
				sd = 1.0f;
				tn = e;
				td = c;
			}
			else
			{
				sn = b * e - c * d;
				tn = a * e - b * d;

				if (sn < 0.0f)
				{
					sn = 0.0;
					tn = e;
					td = c;
				}
				else if (sn > sd)
				{
					sn = sd;
					tn = e + b;
					td = c;
				}
			}

			if (tn < 0.0f)
			{
				tn = 0.0f;

				if (-d < 0.0f) sn = 0.0f;
				else if (-d > a) sn = sd;
				else
				{
					sn = -d;
					sd = a;
				}
			}
			else if (tn > td)
			{
				tn = td;

				if (-d + b < 0.0f) sn = 0.0f;
				else if (-d + b > a) sn = sd;
				else
				{
					sn = -d + b;
					sd = a;
				}
			}

			if (abs(sc) < std::numeric_limits<float>::epsilon()) sc = 0;
			else sc = sn / sd;		// Maybe this part is not checked
			if (abs(tc) < std::numeric_limits<float>::epsilon()) tc = 0;
			else tc = tn / td;	// Maybe this part is not checked as well

			glm::vec3 distanceVec = w + (u * sc) - (v * tc);
			return glm::dot(distanceVec, distanceVec);
		}

		// Minimum distance between a point and a line segment
		float MinDistanceSquaredPointSegment(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, glm::vec3& closest)
		{
			glm::vec3 AB = B - A;
			glm::vec3 AC = C - A;
			glm::vec3 BC = C - B;

			float dot = glm::dot(AC, AB);
			if (dot < 0.0f)
			{
				closest = A;
				std::cout << "Clamped to A" << std::endl;
				// Clamp to A being the closest point
				return glm::dot(AC, AC);
			}
			else if (glm::dot(BC, AB) > 0.0f)
			{
				closest = B;
				std::cout << "Clamped to B" << std::endl;
				// Clamp B to being the closest point
				return glm::dot(BC, BC);
			}
			else
			{
				closest = glm::normalize(AB) * dot;
				std::cout << "Between A and B" << std::endl;
				// Its a point between them so use pythagoras to find it 
				return glm::dot(AC, AC) - (dot * dot);
			}
		}

		// Find the minimum distance from a point to the ray
		float MinDistanceSquaredPointRay(const glm::vec3& point, const glm::vec3& startPointRay, const glm::vec3& rayDirection, glm::vec3& closestPoint)
		{
			float minDistance = 0;	// the minimum distance
			glm::vec3 startPointToRay = point - startPointRay;	// Vector from the point to the starting point of the ray

			float dot = glm::dot(startPointToRay, rayDirection);	// Find the dot product of the ray and the point to start point vector
			float distanceSquaredPointRay = glm::dot(startPointToRay, startPointToRay);	// Squared magnitude of start point of the ray and the point

			if (dot < 0)
			{
				// Clamp on the starting point
				minDistance = distanceSquaredPointRay;	// Return magnitude squared since the start point of the ray is the closest point to the point
				closestPoint = startPointRay;	// If we need it 
			}
			else
			{
				// Clamp onto the ray since it is infinite
				minDistance = distanceSquaredPointRay - (dot * dot);
				closestPoint = glm::normalize(rayDirection) * dot;	// If we need it 
			}

			return minDistance;
		}

		// Minimum distance between a line segment and a ray
		float MinDistanceSquaredLineSegmentRay(const glm::vec3& A, const glm::vec3& B, const glm::vec3& rayStartPoint, const glm::vec3& rayDirection)
		{
			// Check if the line segment and ray intersect
			if (CollisionUtil::LineSegmentRayCollision(A, B, rayStartPoint, rayDirection)) return 0.0f;

			// Calculate the minimum distance from the 3 points that we have and take the minimum one 
			float minimumDistances[3];
			glm::vec3 closestPoint;

			minimumDistances[0] = MinDistanceSquaredPointRay(A, rayStartPoint, rayDirection, closestPoint);
			minimumDistances[1] = MinDistanceSquaredPointRay(B, rayStartPoint, rayDirection, closestPoint);
			minimumDistances[2] = MinDistanceSquaredPointSegment(A, B, rayStartPoint, closestPoint);

			float minDistance = minimumDistances[0];

			// Find the minimum of the 3 and that should be the least distance 
			for (int i = 1; i < 3; i++)
			{
				if (minimumDistances[i] < minDistance) minDistance = minimumDistances[i];
			}

			return minDistance;
		}

		// Do a raycast without checking for filtered colliders 
		Collider* RaycastUnfiltered(const std::map<int, Collider*>& colliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection)
		{
			Ray ray = Ray(rayStartPosition, rayDirection);		// Create a ray in the direction
			std::map<int, Collider*>::const_iterator iter;

			for (iter = colliders.begin(); iter != colliders.end(); ++iter)
			{
				if (iter->second->RaycastCollision(ray)) return iter->second;		// Do the raycast and check for that 
			}

			return NULL;
		}

		// Do a raycast with some filtering of certain user defined filtered colliders 
		Collider* RaycastFiltered(const std::map<int, Collider*>& colliders, const std::vector<Collider*>& filterColliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection)
		{
			Ray ray = Ray(rayStartPosition, rayDirection);	// Create a ray in the direction
			std::map<int, Collider*> filterCollidersMap;	// Map of the filtered colliders
			std::map<int, Collider*>::const_iterator iter;	// Iterator of the collider map

			// Store the vector in a map for quick access (makes filtering much more efficient)
			for (unsigned int i = 0; i < filterColliders.size(); i++)
			{
				filterCollidersMap[filterColliders[i]->colliderId] = filterColliders[i];
			}

			// Go through the colliders checking for raycast collisions after filtering out the ones we don't want 
			for (iter = colliders.begin(); iter != colliders.end(); ++iter)
			{
				if (filterCollidersMap.find(iter->first) != filterCollidersMap.end()) continue;	// If it is filtered then skip the collision check 
				if (iter->second->RaycastCollision(ray)) return iter->second;	// Do the raycast and check for that
			}

			return NULL;
		}

		// Slerp implementation which allows for linear interpolation of rotations
		glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t)
		{
			// if the factor is bad then return an identity quaternion
			if (t < 0 || t > 1) return glm::quat();
			return glm::mix(firstRotation, secondRotation, t);
		}

		// Lerping which is linear interpolation between 2 points 
		glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t)
		{
			// If the factor is wrong return the destination
			if (t < 0 || t > 1) return destination;
			return (1 - t) * startingPosition + t * destination;
		}

		// Easing a value according to a sin curve (in this case at least)
		float Ease(float t)
		{
			if (!t) return NULL;
			return (float)(sin(t * pi - pi / 2.0f) + 1.0f) / 2.0f;
		}
	}
}
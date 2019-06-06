/*
	Author: Brady Jessup
	Description: Contains the parameters to constuct a transform
*/

#include <PrecompiledHeader.h>
#include "Transform.h"

Transform::Transform(const glm::vec3& position, const glm::quat& quaternion, const glm::vec3& scale)
	: position(position), orientation(quaternion), scale(scale)
{}

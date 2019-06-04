/*
	Author: Brady Jessup
	Description: Contains the parameters to constuct a transform
*/

#include <PrecompiledHeader.h>
#include "Transform.h"

Transform::Transform(const glm::vec3& position, const glm::quat& quaternion, const glm::vec3& scale)
	: position(position), orientation(quaternion), scale(scale)
{}

glm::mat4 Transform::ConstructModelMatrix()
{
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotateMatrix = glm::toMat4(orientation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 result = translateMatrix * rotateMatrix * scaleMatrix;
	return result;
}

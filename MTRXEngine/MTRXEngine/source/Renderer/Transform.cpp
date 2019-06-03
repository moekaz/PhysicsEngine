/*
	Author: Brady Jessup
	Description: Contains the parameters to constuct a transform
*/

#include <PrecompiledHeader.h>
#include "Transform.h"

Transform::Transform(glm::vec3& position, glm::quat& quaternion, glm::vec3& scale)
	: position(position), orientation(quaternion), scale(scale)
{
}

glm::mat4 Transform::ConstructModelMatrix()
{
	glm::mat4 translateMatrix = glm::translate(glm::mat4(), position);
	glm::mat4 rotateMatrix = glm::mat4();
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), scale);

	glm::mat4 result = translateMatrix * rotateMatrix * scaleMatrix;
	return result;
}

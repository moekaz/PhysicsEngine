/*
	Author: Brady Jessup
	Description: Contains the parameters to constuct a transform
*/

#pragma once

class Transform
{
public:
	Transform(glm::vec3& position, glm::quat& quaternion, glm::vec3& scale);

	glm::mat4 ConstructModelMatrix();
private:
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scale;
};

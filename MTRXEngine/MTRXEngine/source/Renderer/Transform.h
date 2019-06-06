/*
	Author: Brady Jessup
	Description: Contains the parameters to constuct a transform
*/

#pragma once

class Transform
{
public:
	Transform(const glm::vec3& position, const glm::quat& quaternion, const glm::vec3& scale);
	
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scale;
};

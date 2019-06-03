/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#pragma once

class Camera
{
public:
	Camera();

	void UpdateCamera(float deltaTime);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
private:
	float fov;
	float nearPlane, farPlane;
};

/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#include <PrecompiledHeader.h>
#include "Camera.h"

Camera::Camera()
	: fov(90), nearPlane(0.01f), farPlane(1000.0f)
{

}

void Camera::UpdateCamera(float deltaTime)
{

}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(fov, width / height, nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	//return glm::lookAt();
}

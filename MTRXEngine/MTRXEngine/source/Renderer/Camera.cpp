/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#include <PrecompiledHeader.h>
#include "Camera.h"

Camera::Camera(Window* window)
	: renderWindow(window), fov(90), nearPlane(0.01f), farPlane(1000.0f)
{

}

void Camera::UpdateCamera(float deltaTime)
{

}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(fov, renderWindow->GetAspectRatio(), nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(glm::vec3(0.0f, 2.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

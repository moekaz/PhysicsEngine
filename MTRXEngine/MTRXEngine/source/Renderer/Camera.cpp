/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#include <PrecompiledHeader.h>
#include "Camera.h"

Camera::Camera(Window* window, const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up)
	: renderWindow(window), fov(90), nearPlane(0.01f), farPlane(1000.0f), transform(position, glm::angleAxis(0.f, up)),
	axes(forward, up, glm::normalize(glm::cross(forward, up)))
{}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(fov, renderWindow->GetAspectRatio(), nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(transform.GetPosition(), transform.GetPosition() + GetForward(), GetUp());
}

void Camera::Pitch(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetSide());
	glm::quat& orientation = transform.GetOrientation();
	orientation = rotation * orientation;
}

void Camera::Yaw(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, mtrx::worldUp);
	glm::quat& orientation = transform.GetOrientation();
	orientation = rotation * orientation;
}

void Camera::Roll(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetForward());
	glm::quat& orientation = transform.GetOrientation();
	orientation = rotation * orientation;
}

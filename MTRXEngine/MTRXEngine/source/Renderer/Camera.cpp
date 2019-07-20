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

void Camera::UpdateCamera(float deltaTime)
{
	// Camera movement
	if (mtrx::InputSystem::GetKey(GLFW_KEY_W))
		transform.position += GetForward() * deltaTime * 2.f;
	if (mtrx::InputSystem::GetKey(GLFW_KEY_A))
		transform.position += -GetSide() * deltaTime * 2.f;
	if (mtrx::InputSystem::GetKey(GLFW_KEY_S))
		transform.position += -GetForward() * deltaTime * 2.f;
	if (mtrx::InputSystem::GetKey(GLFW_KEY_D))
		transform.position += GetSide() * deltaTime * 2.f;

	// Camera rotation
	const glm::vec2& offset = mtrx::InputSystem::GetMouseOffset();
	if (offset.x != 0.000001)
		Pitch(offset.x * deltaTime);
	if (offset.y != 0.000001)
		Yaw(-offset.y * deltaTime);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(fov, renderWindow->GetAspectRatio(), nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(transform.position, transform.position + GetForward(), GetUp());
}

void Camera::Pitch(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetSide());
	transform.orientation = rotation * transform.orientation;
}

void Camera::Yaw(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, mtrx::worldUp);
	transform.orientation = rotation * transform.orientation;
}

void Camera::Roll(float angle)
{
	glm::quat rotation = glm::angleAxis(angle, GetForward());
	transform.orientation = rotation * transform.orientation;
}

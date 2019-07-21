/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#pragma once

#include <Window.h>
#include <Defs.h>
#include <Input/InputSystem.h>
#include <math/Transform.h>

class Camera
{
public:
	Camera(Window* window, const glm::vec3& position = glm::vec3(), const glm::vec3& forward = glm::vec3(0, 0, -1.f), const glm::vec3& up = glm::vec3(0, 1.f, 0));

	// TBD: Normalizing this vector should be removed
	inline glm::vec3 GetForward() { return glm::normalize(transform.GetOrientation() * axes.forward); }
	inline glm::vec3 GetSide() { return glm::normalize(transform.GetOrientation() * axes.side); }
	inline glm::vec3 GetUp() { return glm::normalize(transform.GetOrientation() * axes.up); }
	inline mtrx::Transform& GetTransform() { return transform; }

	// Camera matrix calculations
	inline glm::mat4 GetProjectionMatrix() { return glm::perspective(fov, renderWindow->GetAspectRatio(), nearPlane, farPlane); }
	inline glm::mat4 GetViewMatrix() { return glm::lookAt(transform.GetPosition(), transform.GetPosition() + GetForward(), GetUp()); }

	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);

private:
	Window* renderWindow;
	float fov;
	float nearPlane, farPlane;
	mtrx::Transform transform;
	mtrx::ObjectAxes axes;
};

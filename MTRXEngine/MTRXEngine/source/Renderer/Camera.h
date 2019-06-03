/*
	Author: Brady Jessup
	Description: Abstracts the info for camera controls in 3D space
*/

#pragma once

#include "Window.h"

class Camera
{
public:
	Camera(Window* window);

	void UpdateCamera(float deltaTime);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
private:
	Window* renderWindow;

	float fov;
	float nearPlane, farPlane;
};

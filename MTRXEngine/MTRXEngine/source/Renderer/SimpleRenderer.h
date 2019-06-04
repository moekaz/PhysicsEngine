/*
	Author: Brady Jessup
	Description: Contains the definition for a simple renderer for physics testing
*/

#pragma once

#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "Window.h"

class SimpleRenderer {
public:
	SimpleRenderer(Window* window);
	~SimpleRenderer();

	void Render(std::vector<Transform>& transforms);

private:
	void Init();
	void BindCube();

private:
	Window *renderWindow;
	Shader shader;
	Camera camera;

	unsigned int cubeVAO, cubeVBO;
};
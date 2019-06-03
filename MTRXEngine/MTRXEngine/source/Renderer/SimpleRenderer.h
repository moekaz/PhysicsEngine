/*
	Author: Brady Jessup
	Description: Contains the definition for a simple renderer for physics testing
*/

#pragma once

#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class SimpleRenderer {
public:
	SimpleRenderer();
	~SimpleRenderer();

	void Render(std::vector<Transform>& transforms);
private:
	void Init();
	void BindCube();
private:
	Shader shader;
	Camera camera;

	unsigned int cubeVAO, cubeVBO;
};

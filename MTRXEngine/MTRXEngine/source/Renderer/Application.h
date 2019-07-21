#pragma once

#include <Window.h>
#include <SimpleRenderer.h>
#include <Input/InputSystem.h>

class Application
{
public:
	Window window;
	SimpleRenderer renderer;
	InputSystem* inputSystem;
	Camera* camera;

	Application(const char* appName = "MTRX", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, int fps = DEFAULT_FPS);
	~Application();
	
	void Update(float deltaTime);

	// Getters
	inline void PollOpenGlErrors()
	{
		// Poll for opengl errors
		while (GLenum error = glGetError() != GL_NO_ERROR)
		{
			MTRX_ERROR("OpenGL error: " + error);
		}
	}
};
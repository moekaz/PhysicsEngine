#pragma once

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#include <log/LogManager.h>

class Window
{
public:
	Window(const char* windowName, int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
	~Window();

	// Getters
	inline GLFWwindow* GetWindow() { return window; }
	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }
	inline float GetAspectRatio() { return (float)width / (float)height; }

	void Update();
	void InputCheck();
protected:
	GLFWwindow* window;
	int width;
	int height;
};


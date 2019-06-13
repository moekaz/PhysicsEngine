#pragma once

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#include <log/LogManager.h>

struct MouseData
{

};

class Window
{
public:
	static double lastX;
	static double lastY;
	static double xOffset;
	static double yOffset;

	Window(const char* windowName, int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, float fps = 60, bool vsync = true);
	~Window();

	// Getters
	inline GLFWwindow* GetWindow() { return window; }
	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }
	inline float GetAspectRatio() { return (float)width / (float)height; }
	inline bool ShouldClose() { return glfwWindowShouldClose(window); }
	inline bool GetKey(char keyCode) { return glfwGetKey(window, keyCode) != GLFW_RELEASE; }
	inline bool GetKeyDown(char keyCode) { return glfwGetKey(window, keyCode) == GLFW_PRESS; }
	inline bool GetIsVsync() { return vsync; }
	
	inline void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void SetVsync(bool vsync);
	void UpdateBuffers();
	void InputCheck();

protected:
	GLFWwindow* window;
	int width;
	int height;
	float fps;
	bool vsync;
};


#include "PrecompiledHeader.h"
#include "Window.h"

Window::Window(const char* windowName, int width, int height, float fps) : width(width), height(height), fps(fps)
{
	if (!glfwInit())
	{
		MTRX_ERROR("GLFW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}

	// Create a window
	window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
	if (!window)
	{
		MTRX_ERROR("GLFW WINDOW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}
}

Window::~Window()
{
	// Terminate window
	glfwDestroyWindow(window);
}

void Window::UpdateBuffers()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}
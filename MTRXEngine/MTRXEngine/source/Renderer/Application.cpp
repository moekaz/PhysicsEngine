#include <PrecompiledHeader.h>
#include <Application.h>

Application::Application(const char* appName, int width, int height, int fps) : window(appName, width, height, fps), renderer(&window)
{	 
	// Setup opengl viewport
	glViewport(0, 0, width, height);

	// Set the clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// Error callback
	glfwSetErrorCallback([](int error, const char* description) { MTRX_ERROR("ERROR: " + std::string(description)); });

	// Setup opengl viewport callback for when the window size changes to update the viewport
	glfwSetFramebufferSizeCallback(window.GetWindow(), [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	});
}

Application::~Application()
{}

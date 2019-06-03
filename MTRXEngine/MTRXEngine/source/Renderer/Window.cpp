#include "PrecompiledHeader.h"
#include "Window.h"

Window::Window(const char* windowName, int width, int height) : width(width), height(height)
{
	if (!glfwInit())
	{
		MTRX_CRITICAL("GLFW HAS NOT INITIALIZED PROPERLY!!!");
		assert(false);
	}

	// Create a window
	window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
	if (!window)
	{
		MTRX_CRITICAL("GLFW WINDOW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}

	// Make this window the current context window
	glfwMakeContextCurrent(window);

	// Error callback
	glfwSetErrorCallback([](int error, const char* description) { MTRX_ERROR("ERROR: " + std::string(description)); });

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		MTRX_ERROR("Could not initialize GLAD");
		assert(false);
	}

	// Setup opengl viewport
	glViewport(0, 0, width, height);

	// Setup opengl viewport callback for when the window size changes to update the viewport
	glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height); 
	});

	// Set the clear color
	glClearColor(0.f, 1.f, 0.f, 1.f);
}

Window::~Window()
{
	// Terminate window
	glfwDestroyWindow(window);
}

void Window::Update()
{
	while (!glfwWindowShouldClose(window))
	{
		// Check for input
		InputCheck();

		// Do some rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// poll and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Window::InputCheck()
{
	// Check for input here
}
#include "PrecompiledHeader.h"
#include "Window.h"

double Window::lastX = 0;
double Window::lastY = 0;
double Window::xOffset = 0;
double Window::yOffset = 0;


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
	glfwGetCursorPos(window, &Window::lastX, &Window::lastY);
	if (!window)
	{
		MTRX_ERROR("GLFW WINDOW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}

	// Make this window the current context window
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		MTRX_ERROR("Could not initialize GLAD");
		glfwTerminate();
		assert(false);
	}

	// Setup opengl viewport
	glViewport(0, 0, width, height);

	// Set the clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// Error callback
	glfwSetErrorCallback([] (int error, const char* description) { MTRX_ERROR("ERROR: " + std::string(description)); });

	// Setup opengl viewport callback for when the window size changes to update the viewport
	glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height); 
	});

	// Setup key callback
	glfwSetKeyCallback(window, [] (GLFWwindow* window, int key, int scancode, int action, int mods)
	{});

	// Cursor position callback
	glfwSetCursorPosCallback(window, [] (GLFWwindow* window, double xpos, double ypos) 
	{
		Window::xOffset = xpos - Window::lastX;
		Window::yOffset = Window::lastY - ypos;
		Window::lastX = xpos;
		Window::lastY = ypos;
	});

	// Mouse button callback
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) 
	{
		if (action != GLFW_RELEASE)
		{
			// Mouse button pressed or held
			switch (button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
				{
					break;
				}
				case GLFW_MOUSE_BUTTON_RIGHT:
				{
					break;
				}
			}
		}
		else
		{
			// Mouse button was released
		}
	});

	// Scroll callback
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) 
	{});

	// Cursor enter callback
	glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered)
	{
		if (entered == 1)
		{
			// Cursor entered window area
		}
		else
		{
			// Cursor left the window area
		}
	});
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
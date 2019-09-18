#include "PrecompiledHeader.h"
#include "Window.h"

Window::Window(const char* windowName, int width, int height, int fps) : width(width), height(height), fps(fps)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		MTRX_ERROR("GLFW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}

	// Create a window and make it the current context
	window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		MTRX_ERROR("GLFW WINDOW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		MTRX_ERROR("COULD NOT INITIALIZE GLAD");
		glfwTerminate();
		assert(false);
	}

	// Initialize ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init();

	// Setup style
	ImGui::StyleColorsDark();
}

Window::~Window()
{
	// Terminate ImGui
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	// Terminate window
	glfwDestroyWindow(window);
}
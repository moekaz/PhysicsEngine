#include <PrecompiledHeader.h>
#include <log/LogManager.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLFWwindow* window;

void InputTest()
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		MTRX_INFO("A has been pressed");
	}
}

int main()
{
	mtrx::LogManager::init(); // Initialize the logger

	if (!glfwInit())
	{
		MTRX_CRITICAL("GLFW HAS NOT INITIALIZED PROPERLY!!!");
		return -1;
	}

	// Create a window
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO WINDOW", nullptr, nullptr);
	if (!window)
	{
		MTRX_CRITICAL("GLFW WINDOW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		return -1;
	}

	// Make this window the current context window
	glfwMakeContextCurrent(window);

	// Error callback
	glfwSetErrorCallback([](int error, const char* description) { MTRX_ERROR("ERROR: " + std::string(description)); });

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		MTRX_ERROR("Could not initialize GLAD");
		return -1;
	}

	// Setup opengl viewport
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Setup opengl viewport callback for when the window size changes to update the viewport
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow * window, int width, int height) { glViewport(0, 0, width, height); });

	// Set the clear color
	glClearColor(1.f, 0.f, 0.f, 1.f);

	// Setup while loop for window
	while (!glfwWindowShouldClose(window))
	{
		// Check for input 
		InputTest();

		// Rendering call
		glClear(GL_COLOR_BUFFER_BIT);
	
		// Get Events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Done when done with glfw to deallocate window data and other information
	glfwTerminate();

	return 0;
}
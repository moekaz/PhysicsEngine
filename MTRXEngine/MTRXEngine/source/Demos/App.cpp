#include <PrecompiledHeader.h>
#include <../Demos/App.h>

App::App(const char* appName, int width, int height) : window(appName, width, height), renderer(window)
{
	mtrx::LogManager::init();
	glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

App::~App()
{}

void App::Update()
{
	// Check for input 
	BaseInputCheck();

	// Clear the window
	window.Clear();

	// Update the rigidbody and the particle system
	rbManager.PhysicsUpdate();
	pManager.PhysicsUpdate();

	// Update renderer
	renderer.GetCamera()->UpdateCamera(mtrx::GameTime::deltaTime);
	renderer.Render(transformsToRender);

	// Clear buffers and poll
	window.UpdateBuffers();

	// Update delta time
	mtrx::GameTime::PhysicsUpdate();
}

void App::BaseInputCheck()
{
	if (window.GetKeyDown(GLFW_KEY_G))
	{
		cursor = !cursor;
		if (cursor)
			glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}
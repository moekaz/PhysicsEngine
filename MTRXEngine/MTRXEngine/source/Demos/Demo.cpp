#include <PrecompiledHeader.h>
#include <../Demos/Demo.h>

Demo::Demo(const char* appName, int width, int height) : application(appName, width, height), cursor(false)
{
	// TODO: Abstract this in window code 
	glfwSetInputMode(application.window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Demo::~Demo()
{}

void Demo::Update()
{
	while (!application.window.ShouldClose())
	{
		// Basic input checks that will shared by all applications
		mtrx::InputSystem::Update();
		BaseInputCheck();
		InputCheck();

		// Poll for opengl errors
		while (GLenum error = glGetError() != GL_NO_ERROR)
		{
			MTRX_ERROR("OpenGL error: " + error);
		}

		// Clear the window
		application.window.Clear();

		// Update the rigidbody and the particle system
		rbManager.PhysicsUpdate();
		pManager.PhysicsUpdate();

		// Update renderer
		application.renderer.GetCamera()->UpdateCamera(mtrx::GameTime::deltaTime);
		application.renderer.Render(transformsToRender);

		// Clear buffers and poll
		application.window.UpdateBuffers();

		// Update delta time
		mtrx::GameTime::PhysicsUpdate();
	}
}

void Demo::BaseInputCheck()
{
	if (mtrx::InputSystem::GetKeyDown(GLFW_KEY_G))
	{
		cursor = !cursor;
		if (cursor)
			glfwSetInputMode(application.window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(application.window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Demo::Run()
{
	mtrx::GameTime::Init();
	Update();
}
#include <PrecompiledHeader.h>
#include <log/LogManager.h>
#include <Window.h>
#include <SimpleRenderer.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>
#include <forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h>

int main()
{
	// Initialize the logger
	mtrx::LogManager::init();

	// Create a window and a renderer(which creates a camera)
	Window window = Window("DEMO WINDOW", 800, 600);
	SimpleRenderer renderer = SimpleRenderer(&window);

	// Create a bunch of transforms
	std::vector<mtrx::Transform*> transformsToRender;
	glm::quat orientation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Rigidbodies
	mtrx::Rigidbody body1 = mtrx::Rigidbody(1.f, false, glm::vec3(), glm::quat(), glm::vec3(1, 1, 1));

	// Force generators
	mtrx::rb_GravityForceGenerator gravityGenerator = mtrx::rb_GravityForceGenerator(glm::vec3(0, -mtrx::gravity * 2.f, 0));
	mtrx::rb_BuoyancyForceGenerator buoyancyGenerator = mtrx::rb_BuoyancyForceGenerator(3.f, 1.f, 1.5f, 1000.f);
	
	transformsToRender.push_back(body1.GetTransform());

	mtrx::GameTime::Init();

	// Game loop
	while (!window.ShouldClose())
	{	
		// Check for input
		//window.InputCheck();

		// Clear the window
		window.Clear();

		glm::vec3 pos = body1.GetPosition();
		std::cout << "position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;

		// CHECK EVERY TYPE OF FORCE GENERATOR
		//gravityGenerator.UpdateForces(&body1);
		buoyancyGenerator.UpdateForces(&body1);

		// ADD A FORCE ON A RIGIDBODY and test the nivenebt properly	
		//body1.AddForce(glm::vec3(0, -200.f, 0.f));

		// ADD A FORCE AT A POINT TO A RIGIDBODY
		//body1.AddForceAtPoint(glm::vec3(-1.f ,0,-10.f) , body1.GetPosition() + glm::vec3(0.2f, 0, 0));

		// CHECK FOR COLLISIONS

		// Update with rigidbody integration 
		body1.PhysicsUpdate();
		renderer.GetCamera()->UpdateCamera(mtrx::GameTime::deltaTime);

		// Render
		renderer.Render(transformsToRender);

		// Clear buffers and poll
		window.UpdateBuffers();

		// Update delta time
		mtrx::GameTime::PhysicsUpdate();
		std::cout << "delta time: " << mtrx::GameTime::deltaTime << std::endl;
	}

	return 0;
}

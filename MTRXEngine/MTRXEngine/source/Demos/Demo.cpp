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
	mtrx::LogManager::init(); // Initialize the logger

	// CREATE A CAMERA WHICH IS UPDATEABLE AND MOEVABLE

	// Create a window and a renderer
	Window window = Window("DEMO WINDOW", 800, 600);
	SimpleRenderer renderer = SimpleRenderer(&window);

	// Create a bunch of transforms
	std::vector<mtrx::Transform*> transformsToRender;
	float angle = 0.0f;
	glm::quat orientation = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	mtrx::Rigidbody body1 = mtrx::Rigidbody(1.f, false, glm::vec3(), glm::quat(), glm::vec3(1, 1, 1));
	mtrx::rb_GravityForceGenerator gravityGenerator = mtrx::rb_GravityForceGenerator(glm::vec3(0, -mtrx::gravity, 0));
	mtrx::rb_BuoyancyForceGenerator buoyancyGenerator = mtrx::rb_BuoyancyForceGenerator(3.f, 1.f, 1.5f, 1000.f);
	
	transformsToRender.push_back(body1.GetTransform());
	//transformsToRender.push_back(Transform(glm::vec3(0.0f, 0.0f, 0.0f), orientation, glm::vec3(1.0f, 1.0f, 1.0f)));

	// Game loop
	while (!window.ShouldClose())
	{
		// Check for input
		//window.InputCheck();

		// Clear the window
		window.Clear();

		// CHECK EVERY TYPE OF FORCE GENERATOR

		// ADD A FORCE ON A RIGIDBODY and test the nivenebt properly

		// ADD A FORCE AT A POINT TO A RIGIDBODY
		// TEST INTEGRATION 

		// Update delta time
		mtrx::GameTime::PhysicsUpdate();


		glm::vec3 pos = body1.GetPosition();
		std::cout << "position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;

		body1.AddForce(glm::vec3(0,0,-10.f));
		//body1.AddForceAtPoint(glm::vec3(-1.f ,0,-10.f) , body1.GetPosition() + glm::vec3(0.2f, 0, 0));
		// Update the body and its forces and make sure they work properly 
		//gravityGenerator.UpdateForces(&body1);
		//buoyancyGenerator.UpdateForces(&body1);
		body1.PhysicsUpdate();

		// CHECK FOR COLLISIONS

		renderer.GetCamera()->UpdateCamera(mtrx::GameTime::deltaTime);

		// Render
		renderer.Render(transformsToRender);

		// Clear buffers and poll
		window.UpdateBuffers();
	}

	return 0;
}

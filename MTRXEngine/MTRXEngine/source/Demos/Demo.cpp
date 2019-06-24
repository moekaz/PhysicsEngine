#include <PrecompiledHeader.h>
#include <log/LogManager.h>
#include <Window.h>
#include <SimpleRenderer.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>
#include <forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h>
#include <RigidbodyManager.h>
#include <ParticleManager.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>

int main()
{
	// Initialize the logger
	mtrx::LogManager::init();

	// Create a window and a renderer(which creates a camera)
	Window window = Window("DEMO WINDOW", 800, 600);
	SimpleRenderer renderer = SimpleRenderer(&window);
	std::vector<mtrx::Transform*> transformsToRender;
	
	// Physics entity manager
	mtrx::RigidbodyManager rbManager;
	mtrx::ParticleManager pManager;

	glm::quat orientation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Rigidbodies
	mtrx::Rigidbody body1 = mtrx::Rigidbody(1.f, false, glm::vec3(0.f, 2.f, 0.f), orientation, glm::vec3(1.f, 1.f, 1.f));
	float extents[3] = { 1.f, 1.f, 1.f };
	body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(1.f, extents));

	mtrx::Rigidbody artillery;

	// Force generators
	mtrx::rb_GravityForceGenerator gravityGenerator = mtrx::rb_GravityForceGenerator(glm::vec3(0, -mtrx::gravity, 0));

	// Fix buoyancy generator
	mtrx::rb_BuoyancyForceGenerator buoyancyGenerator = mtrx::rb_BuoyancyForceGenerator(0.0001f, 0.5f, 1.f);

	//rbManager.AddRigidbody(&body1);
	//rbManager.AddForceGenerator(&body1, &gravityGenerator);
	//rbManager.AddForceGenerator(&body1, &buoyancyGenerator);
	
	// This is just a reference transform
	mtrx::Transform center = mtrx::Transform(glm::vec3(0, 1.f, 0), glm::quat(), glm::vec3(0.1f, 0.1f, 0.1f));

	//transformsToRender.push_back(body1.GetTransform());
	transformsToRender.push_back(&center);
	//transformsToRender.push_back(artillery.GetTransform());
	
	// window options
	glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSwapInterval(0);
	 
	mtrx::GameTime::Init();

	// Game loop
	while (!window.ShouldClose())
	{	
		// Check for input
		//window.InputCheck();

		// Clear the window
		window.Clear();

		glm::vec3 pos = artillery.GetPosition();
		std::cout << "position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;

		if (window.GetKeyDown(GLFW_KEY_SPACE))
		{
			rbManager.RemoveRigidbody(&artillery);
			transformsToRender.erase(transformsToRender.begin() + transformsToRender.size() - 1);
			glm::quat orientation1 = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			artillery = mtrx::Rigidbody(2.f, false, glm::vec3(-1.f, 0.f, 0.f), orientation1, glm::vec3(1.f, 1.f, 1.f));
			artillery.SetAngularDamping(0.9f);
			artillery.SetLinearDamping(0.9f);
			transformsToRender.push_back(artillery.GetTransform());
			rbManager.AddRigidbody(&artillery);
			//rbManager.AddForceGenerator(&artillery, &gravityGenerator);
			//artillery.SetVelocity(glm::vec3(3, 2, 0));
			
			//artillery.SetAcceleration(glm::vec3(0, -2.f, 0));
			//artillery.AddForce(glm::vec3(3000.f, 2000.f, 0));
			artillery.AddForceAtPoint(glm::vec3(300.0f, 0.f, 0.f), artillery.GetPosition() + glm::vec3(0.5f, 0, -0.5f));
		}

		// CHECK EVERY TYPE OF FORCE GENERATOR
		// Update rigidbodies force generators and check for collisions
		//pManager.PhysicsUpdate();
		rbManager.PhysicsUpdate();

		// Update renderer
		renderer.GetCamera()->UpdateCamera(mtrx::GameTime::deltaTime);
		renderer.Render(transformsToRender);

		// Clear buffers and poll
		window.UpdateBuffers();

		// Update delta time
		mtrx::GameTime::PhysicsUpdate();
	}

	return 0;
}

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
	mtrx::Rigidbody body1 = mtrx::Rigidbody(1.f, false, glm::vec3(0,2.f,0.f), orientation, glm::vec3(1, 1, 1));
	float extents[3] = { 1.f, 1.f, 1.f };
	glm::mat3 it = mtrx::GenerateCuboidIT(1.f, extents);
	//std::cout << it[0][0] << " " << it[1][1] << " " << it[2][2] << std::endl;

	body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(1.f, extents));
	//glm::mat3 mat = body1.GetInverseInertiaTensor();

	//std::cout << mat[0][0] << " " << mat[1][1] << " " << mat[2][2] << std::endl;

	// Force generators
	mtrx::rb_GravityForceGenerator gravityGenerator = mtrx::rb_GravityForceGenerator(glm::vec3(0, -mtrx::gravity, 0));
	mtrx::rb_BuoyancyForceGenerator buoyancyGenerator = mtrx::rb_BuoyancyForceGenerator(1.f, 1.f, 1.f);
	
	mtrx::Transform center = mtrx::Transform(glm::vec3(0, 1.f, 0), glm::quat(), glm::vec3(0.05f, 0.05f, 0.05f));

	transformsToRender.push_back(body1.GetTransform());
	transformsToRender.push_back(&center);

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
		//buoyancyGenerator.UpdateForces(&body1);

		// ADD A FORCE AT A POINT ON THE RIGIDBODY
		//body1.AddForceAtPoint(glm::vec3(10.0f, 0.f,0.f) , body1.GetPosition() + glm::vec3(0.5f, 0, -0.5f));
		//body1.AddTorque(glm::vec3(0.f, 0.f, 10));
		
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
		//std::cout << "delta time: " << mtrx::GameTime::deltaTime << std::endl;
	}

	return 0;
}

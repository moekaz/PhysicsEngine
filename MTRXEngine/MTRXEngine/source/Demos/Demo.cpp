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
#include <colliders/BoxCollider.h>
#include <colliders/SphereCollider.h>
#include <colliders/CapsuleCollider.h>

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

	// Rigidbodies
	glm::quat orientation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	mtrx::Rigidbody body1 = mtrx::Rigidbody(1.f, false, glm::vec3(0.f, 1.f, 0.f), orientation, glm::vec3(1.f, 1.f, 1.f));
	float extents[3] = { 1.f, 1.f, 1.f };
	body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(1.f, extents));
	mtrx::Collider* collider = new mtrx::CapsuleCollider();

	// Second box
	glm::quat orientation1 = glm::angleAxis(0.0f, glm::vec3(0, 0, 0));
	mtrx::Rigidbody body2 = mtrx::Rigidbody(1.f, false, glm::vec3(-3.f, 1.f, 0.f), orientation1, glm::vec3(1.f, 1.f, 1.f));
	body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(1.f, extents));
	mtrx::Collider* collider1 = new mtrx::CapsuleCollider();

	// Artillery object 
	mtrx::Rigidbody artillery;

	// Force generators
	mtrx::rb_GravityForceGenerator gravityGenerator = mtrx::rb_GravityForceGenerator(glm::vec3(0, -mtrx::gravity, 0));

	// Fix buoyancy generator
	//mtrx::rb_BuoyancyForceGenerator buoyancyGenerator = mtrx::rb_BuoyancyForceGenerator(0.0001f, 0.5f, 1.f);

	rbManager.AddRigidbody(&body1);
	rbManager.AddRigidbody(&body2);

	//rbManager.AddForceGenerator(&body1, &gravityGenerator);
	//rbManager.AddForceGenerator(&body1, &buoyancyGenerator);
	
	// This is just a reference transform
	mtrx::Transform center =
	{
		glm::vec3(0, 0, 0),
		glm::quat(),
		glm::vec3(0.1f, 0.1f, 0.1f),
	};
	
	transformsToRender.push_back(&center);
	
	// window options
	glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	 
	mtrx::GameTime::Init();


	bool started = false;
	bool cursor = false;

	// Game loop
	while (!window.ShouldClose())
	{	
		// Check for input
		//window.InputCheck();

		// Clear the window
		window.Clear();

		//glm::vec3 pos = artillery.GetPosition();
		//std::cout << "position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;

		if (window.GetKeyDown(GLFW_KEY_SPACE))
		{
			body1 = mtrx::Rigidbody(1.f, false, glm::vec3(0.f, 1.f, 0.f), orientation, glm::vec3(1.f, 1.f, 1.f));
			body2 = mtrx::Rigidbody(1.f, false, glm::vec3(-3.f, 1.f, 0.f), orientation1, glm::vec3(1.f, 1.f, 1.f));

			body1.AddForce(glm::vec3(-10.f, 0.f, 0.f));
			body2.AddForce(glm::vec3(10.f, 0.0f, 0.0f));

			transformsToRender.push_back(body1.GetTransform());
			transformsToRender.push_back(body2.GetTransform());

			started = true;
			//rbManager.RemoveRigidbody(&artillery);
			//transformsToRender.erase(transformsToRender.begin() + transformsToRender.size() - 1);
			//glm::quat orientation1 = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			//artillery = mtrx::Rigidbody(2.f, false, glm::vec3(-1.f, 0.f, 0.f), orientation1, glm::vec3(1.f, 1.f, 1.f));
			//artillery.SetAngularDamping(0.9f);
			//artillery.SetLinearDamping(0.9f);
			//transformsToRender.push_back(artillery.GetTransform());

			//rbManager.AddRigidbody(&artillery);
			//rbManager.AddForceGenerator(&artillery, &gravityGenerator);
			//artillery.SetVelocity(glm::vec3(3, 2, 0));
			
			//artillery.SetAcceleration(glm::vec3(0, -2.f, 0));
			//artillery.AddForce(glm::vec3(3000.f, 2000.f, 0));
			//artillery.AddForceAtPoint(glm::vec3(0.0f, 0.f, -1000.f), artillery.GetPosition() + glm::vec3(0.0f, 0.5f, 0.0f));
		}

		if (window.GetKeyDown(GLFW_KEY_G))
		{
			cursor = !cursor;
			if(cursor)
				glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			else
				glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		// CHECK EVERY TYPE OF FORCE GENERATOR
		// Update rigidbodies force generators and check for collisions
		//pManager.PhysicsUpdate();
		rbManager.PhysicsUpdate();

		if (started)
		{
			// Update the colliders
			collider->SetPosition(body1.GetPosition());
			collider1->SetPosition(body2.GetPosition());

			glm::vec3 pos = collider->GetPosition();
			glm::vec3 pos1 = collider1->GetPosition();
			std::cout << "position1: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
			std::cout << "position2: " << pos1.x << " " << pos1.y << " " << pos1.z << std::endl;

			if (collider->CheckCollision(*collider1))
			{
				std::cout << "collision" << std::endl;
				transformsToRender.clear();
				rbManager.RemoveRigidbody(&body1);
				rbManager.RemoveRigidbody(&body2);
				started = false;
			}
		}

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

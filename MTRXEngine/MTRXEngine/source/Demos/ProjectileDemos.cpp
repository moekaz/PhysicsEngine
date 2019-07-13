#include <PrecompiledHeader.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>
#include <forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <../Demos/App.h>

int main()
{	
	// Create application
	App app = App("PROJECTILE DEMO");

	mtrx::Rigidbody projectile;
	mtrx::rb_GravityForceGenerator gravityGenerator = mtrx::rb_GravityForceGenerator(glm::vec3(0, -mtrx::gravity, 0));
	
	// This is just a reference point in world space
	mtrx::Transform center =
	{
		glm::vec3(0, 0, 0),
		glm::angleAxis(0.f, mtrx::worldUp),
		glm::vec3(0.1f, 0.1f, 0.1f),
	};
	app.transformsToRender.push_back(&center);
	 
	mtrx::GameTime::Init();

	// Game loop
	while (!app.window.ShouldClose())
	{	
		if (app.window.GetKeyDown(GLFW_KEY_SPACE))
		{
			float mass = 1.f;
			float extents[] = { 1.f, 1.f, 1.f };
			projectile = mtrx::Rigidbody(mass, false, glm::vec3(0.f, 1.f, 0.f), glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(1.f, 1.f, 1.f), mtrx::GenerateCuboidIT(mass, extents));
			
			projectile.AddForce(glm::vec3(30.f, 15.f, 0));
		}

		// Update application
		app.Update();
	}

	return 0;
}

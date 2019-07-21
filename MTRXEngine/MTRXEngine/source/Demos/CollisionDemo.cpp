#include <PrecompiledHeader.h>
#include <../Demos/CollisionDemo.h> 

CollisionDemo::CollisionDemo() : Demo("COLLISION DEMO")
{}

CollisionDemo::~CollisionDemo()
{
	delete collider1;
	delete collider2;
}

void CollisionDemo::Update()
{
	// Thinking about creating a fps shooting demo with collision detection and force generation
	
	// This is just a reference point in world space
	mtrx::Transform center =
	{
		glm::vec3(0, 0, 0),
		glm::angleAxis(0.f, mtrx::worldUp),
		glm::vec3(0.1f, 0.1f, 0.1f),
	};
	transformsToRender.insert(&center);

	glm::quat orientation1 = glm::angleAxis(0.f, mtrx::worldUp);
	glm::quat orientation2 = glm::angleAxis(0.f, mtrx::worldUp);

	float mass1 = 1.f;
	float mass2 = 1.f;
	
	float extents[3] = {1, 1, 1};
	
	// Rigidbody declaration 
	body1 = mtrx::Rigidbody(mass1, false, glm::vec3(2, 0, 0), orientation1, glm::vec3(extents[0], extents[1], extents[2]));
	body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(mass1, extents));
	body2 = mtrx::Rigidbody(mass2, false, glm::vec3(-2, 0, 0), orientation2, glm::vec3(extents[0], extents[1], extents[2]));
	body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(mass2, extents));

	// Capsule Colliders
	//collider1 = new mtrx::CapsuleCollider(body1.GetPosition());
	//collider2 = new mtrx::CapsuleCollider(body2.GetPosition());

	// Sphere Colliders
	//collider1 = new mtrx::SphereCollider(body1.GetPosition());
	//collider2 = new mtrx::SphereCollider(body2.GetPosition());

	//// Box Colliders
	collider1 = new mtrx::BoxCollider(body1.GetPosition());
	collider2 = new mtrx::BoxCollider(body2.GetPosition());

	// Rigidbody additions
	rbManager.AddRigidbody(&body1);
	rbManager.AddRigidbody(&body2);

	// Add the transforms of these rigidbodies
	transformsToRender.insert(&body1.GetTransform());
	transformsToRender.insert(&body2.GetTransform());

	// Update loop
	while (!application.window.ShouldClose())
	{
		// Update collider
		collider1->SetPosition(body1.GetPosition());
		collider2->SetPosition(body2.GetPosition());
		collider1->SetRotation(body1.GetOrientation());
		collider2->SetRotation(body2.GetOrientation());

		if (collider1->CheckCollision(*collider2))
		{
			// Collision
			//std::cout << "collision" << std::endl;
		}

		// Update the demo
		Demo::Update();
	}
}

void CollisionDemo::InputCheck()
{
	if (application.inputSystem->GetKeyDown(GLFW_KEY_SPACE))
	{
		body1.AddForce(glm::vec3(-10, 0, 0));
		body2.AddForce(glm::vec3(10, 0, 0));
	}
}
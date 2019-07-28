#include <PrecompiledHeader.h>
#include <../Demos/CollisionDemo.h> 

CollisionDemo::CollisionDemo() : Demo("COLLISION DEMO")
{
	// Setup the world with a bunch of objects
	// This is just a reference point in world space
	mtrx::Transform center =
	{
		glm::vec3(0, 0, 0),
		glm::angleAxis(0.f, mtrx::worldUp),
		glm::vec3(0.1f, 0.1f, 0.1f),
	};
	this->transformsToRender.insert(&center);

	glm::quat orientation1 = glm::angleAxis(0.f, mtrx::worldUp);
	glm::quat orientation2 = glm::angleAxis(150.f, glm::vec3(0, 1, 0));

	float mass1 = 1.f;
	float mass2 = 1.f;

	float extents[3] = { 1, 1, 1 };

	// Rigidbody declaration 
	mtrx::Rigidbody* body1 = new mtrx::Rigidbody(mass1, false, glm::vec3(2, 0, 0), orientation1, glm::vec3(extents[0], extents[1], extents[2]));
	body1->SetInverseInertiaTensor(mtrx::GenerateCuboidIT(mass1, extents));
	mtrx::Rigidbody* body2 = new mtrx::Rigidbody(mass2, false, glm::vec3(-2, 0, 0), orientation2, glm::vec3(extents[0], extents[1], extents[2]));
	body2->SetInverseInertiaTensor(mtrx::GenerateCuboidIT(mass2, extents));


	// Capsule Colliders
	//collider1 = new mtrx::CapsuleCollider(body1.GetPosition());
	//collider2 = new mtrx::CapsuleCollider(body2.GetPosition());

	// Sphere Colliders
	//collider1 = new mtrx::SphereCollider(body1.GetPosition());
	//collider2 = new mtrx::SphereCollider(body2.GetPosition());

	// Box Colliders
	mtrx::Collider* collider1 = new mtrx::BoxCollider(body1->GetPosition());
	mtrx::Collider* collider2 = new mtrx::BoxCollider(body2->GetPosition());

	worldRbs.push_back(body1);
	worldRbs.push_back(body2);

	worldColliders.push_back(collider1);
	worldColliders.push_back(collider2);

	// Rigidbody additions
	rbManager.AddRigidbody(body1);
	rbManager.AddRigidbody(body2);

	// Add the transforms of these rigidbodies
	transformsToRender.insert(&body1->GetTransform());
	transformsToRender.insert(&body2->GetTransform());
}

CollisionDemo::~CollisionDemo()
{}

void CollisionDemo::Update()
{
	// Thinking about creating a fps shooting demo with collision detection and force generation

	// Update loop
	while (!application.window.ShouldClose())
	{
		// Update colliders
		for (int i = 0; i < bulletRbs.size(); ++i)
		{
			bulletColliders[i]->SetPosition(bulletRbs[i]->GetPosition());
			bulletColliders[i]->SetOrientation(bulletRbs[i]->GetOrientation());
		}

		// Check for collision 
		for (int i = 0; i < bulletColliders.size(); ++i)
		{
			for (int j = 0; j < worldColliders.size(); ++j)
			{
				if (bulletColliders[i]->CheckCollision(*worldColliders[i]))
				{
					// Collision
					std::cout << "collision" << std::endl;
					mtrx::Rigidbody* bullet = bulletRbs[i];
					mtrx::Collider* collider = bulletColliders[i];

					worldRbs[j]->AddForceAtPoint(bulletRbs[i]->GetVelocity(), bulletRbs[i]->GetPosition());

					rbManager.RemoveRigidbody(bulletRbs[i]);
					transformsToRender.erase(&bulletRbs[i]->GetTransform());					
					bulletRbs.erase(bulletRbs.begin() + i);
					bulletColliders.erase(bulletColliders.begin() + i);
					
					delete bullet;
					delete collider;

					--i;
					continue;
				}
			}
		}

		// Update the demo
		Demo::Update();
	}
}

void CollisionDemo::InputCheck()
{
	if (application.inputSystem->GetKeyDown(GLFW_KEY_SPACE))
	{
		Shoot();
		//body1.AddForce(glm::vec3(-10, 0, 0));
		//body2.AddForce(glm::vec3(10, 0, 0));
	}
}

void CollisionDemo::Shoot()
{
	// We are shooting a bullet like an fps game
	
	float extents[3] = {1, 1, 1};
	float mass = 1.f;
	glm::vec3 forward = application.camera->GetForward();
	mtrx::Rigidbody* bullet = new mtrx::Rigidbody(mass, false, application.camera->GetTransform().GetPosition() + forward * 0.5f, glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(0.1, 0.1, 0.1), mtrx::GenerateCuboidIT(mass, extents));
	mtrx::Collider* collider = new mtrx::BoxCollider(bullet->GetTransform());

	// Add a force going in the forward direction from the camera with some scalar for magnitude
	bullet->AddForce(forward * 2000.f);

	bulletRbs.push_back(bullet);
	bulletColliders.push_back(collider);
	transformsToRender.insert(&bullet->GetTransform());
	rbManager.AddRigidbody(bullet);
}
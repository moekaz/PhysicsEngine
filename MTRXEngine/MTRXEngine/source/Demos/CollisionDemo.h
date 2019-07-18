#pragma once

#include <../Demos/Demo.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>
#include <colliders/Collider.h>
#include <colliders/BoxCollider.h>
#include <colliders/SphereCollider.h>
#include <colliders/CapsuleCollider.h>

class CollisionDemo : public Demo
{
public:
	mtrx::Rigidbody body1;
	mtrx::Rigidbody body2;
	mtrx::Collider* collider1;
	mtrx::Collider* collider2;

	CollisionDemo();
	~CollisionDemo();

	virtual void Update() override;
	virtual void InputCheck() override;
};
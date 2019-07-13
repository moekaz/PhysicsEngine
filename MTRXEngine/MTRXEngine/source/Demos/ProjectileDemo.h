#pragma once

#include <../Demos/App.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>

class ProjectileDemo : public App
{
public:
	mtrx::Rigidbody projectile;
	mtrx::rb_GravityForceGenerator gravityGenerator;
	int projectileType;

	ProjectileDemo();
	~ProjectileDemo();

	virtual void Update() override;
	virtual void InputCheck() override;
};
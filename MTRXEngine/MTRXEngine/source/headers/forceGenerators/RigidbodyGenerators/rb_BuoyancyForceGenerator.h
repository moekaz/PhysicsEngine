/*
	Author: Mohamed Kazma
	Description: A force generator that allows us to apply buoyancy forces (forces applied by water to keep something afloat also known as the archimedes force)
*/

#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>
#include <entities/Rigidbody.h>
#include <Defs.h>

namespace mtrx
{
	class rb_BuoyancyForceGenerator : public IRigidbodyForceGenerator
	{	
	public:
		LiquidProperties liquidProperties;
		float liquidHeight; // The y coordinate of the liquid's plane (assuming that plane is parallel to XZ plane)
		float maxParticleDepth; // The max depth after which the object is said to be completely submerged (position is from the center to this will affect depth calculation)

		rb_BuoyancyForceGenerator(float volume, float maxPaticleDepth, float liquidHeight = 0.f, float density = 1000.f);
		~rb_BuoyancyForceGenerator();

		virtual void UpdateForces(Rigidbody* rb) override;
	};
}


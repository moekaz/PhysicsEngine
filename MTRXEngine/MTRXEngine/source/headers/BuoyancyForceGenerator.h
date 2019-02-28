/*
	Author: Mohamed Kazma
	Description: A force generator that allows us to apply buoyancy forces (forces applied by water to keep something afloat also known as the archimedes force)
*/

#pragma once

#include <IForceGenerator.h>
#include <Particle.h>

namespace MTRX
{
	class BuoyancyForceGenerator : public IForceGenerator
	{	
	public:
		LiquidProperties liquidProperties;
		float liquidHeight; // The y coordinate of the liquid's plane (assuming that plane is parallel to XZ plane)
		float maxParticleDepth; // The max depth after which the object is said to be completely submerged (position is from the center to this will affect depth calculation)

		virtual void UpdateForces(Particle* particle);
		
		BuoyancyForceGenerator(float density, float volume, float maxPaticleDepth);
		~BuoyancyForceGenerator();
	};
}


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
		float liquidHeight; // The height of the liquid's top of the plane (is parallel to the XZ plane that is the assumption atm)
		float particleDepth;		

		virtual void UpdateForces(Particle* particle);
		
		BuoyancyForceGenerator(float density, float volume, float depth, float paticleDepth);
		~BuoyancyForceGenerator();
	};
}


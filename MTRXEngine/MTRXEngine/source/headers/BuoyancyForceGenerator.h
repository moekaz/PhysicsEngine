#pragma once

#include <IForceGenerator.h>
namespace MTRX
{
	class BuoyancyForceGenerator : public IForceGenerator
	{	
	public:
		virtual void UpdateForces(Particle* particle);
		
		BuoyancyForceGenerator();
		~BuoyancyForceGenerator();
	};
}


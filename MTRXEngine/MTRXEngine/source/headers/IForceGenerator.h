/*
	Author: Mohamed Kazma
	Description: Interface that allows us to define different force patterns for different types of objects
*/
#pragma once

#include <Particle.h>

namespace MTRX
{
	class IForceGenerator
	{
	public:
		virtual void UpdateForces(Particle& particle) = 0; // Allows us to have some specific types of forces generated on a specific type of particle
	protected:
	};
}
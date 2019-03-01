/*
	Author: Mohamed Kazma
	Description: A drag force generator
*/

#pragma once

#include <entities/Particle.h>
#include <forceGenerators/IForceGenerator.h>

namespace MTRX
{
	class DragForceGenerator : public IForceGenerator
	{
	public:
		float k1; // Velocity drag coefficient
		float k2; // Velocity squared drag coefficient

		// Implementation of drag forces on a particle
		virtual void UpdateForces(Particle& particle);
		
		DragForceGenerator(float k1, float k2);
		~DragForceGenerator();

		inline void setK1(float k1) { this->k1 = k1; }
		inline void setK2(float k2) { this->k2 = k2; }
	};
}


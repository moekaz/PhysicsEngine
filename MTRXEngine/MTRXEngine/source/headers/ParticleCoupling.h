/*
	Author: Mohamed Kazma
	Description: Couples to particles as if connected by a cable or link and forces them to remain close to each 
	This can be done using something like particle contacts when the link or cable is taut and this will create an
	impulse which will move them back together
*/

#pragma once

#include <entities/Particle.h>
#include <ParticleCollision.h>

namespace MTRX
{
	class ParticleCoupling
	{
	public:
		Particle* particles[2]; // The 2 particles to be coupled

		ParticleCoupling();
		~ParticleCoupling();

		float GetCurrentLengthSqr() const; // Gives us the length of the cable/ rod that connects the particles squared
		virtual void GenerateContact(ParticleCollision& collision) = 0; // Create a contact collision if the link is taut enough
	private:
	};
}

/*
	Author: Mohamed Kazma
	Description: A particle coupling that uses a rod which is far more stiff than a cable so there is no bounciness 
	or leeway when it comes to the length of the coupling
*/

#pragma once

#include <ParticleCoupling.h>

namespace MTRX
{
	class ParticleRodCoupling : public ParticleCoupling
	{
	public:
		float lengthSqr; // Length of the rod

		ParticleRodCoupling(float lengthSqr);
		~ParticleRodCoupling();

		// THIS MIGHT NEED TO BE REDONE
		virtual void GenerateContact(std::list<ParticleCollision>& collisions, unsigned int limit); // Implementation of the generation of a contact with a rod
	};
}

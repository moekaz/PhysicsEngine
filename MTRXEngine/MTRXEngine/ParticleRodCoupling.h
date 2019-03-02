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
		float length; // Length of the rod

		ParticleRodCoupling(float length);
		~ParticleRodCoupling();

		virtual void GenerateContact(ParticleCollision& collision); // Implementation of the generation of a contact with a rod
	};
}

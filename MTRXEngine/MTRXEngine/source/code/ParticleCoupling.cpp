#include "PrecompiledHeader.h"
#include "ParticleCoupling.h"

namespace MTRX
{
	ParticleCoupling::ParticleCoupling()
	{}

	ParticleCoupling::~ParticleCoupling()
	{}

	float ParticleCoupling::GetCurrentLengthSqr() const
	{
		// Using squared value saves us a lot on speed
		return glm::length2(particles[0]->GetPosition() - particles[1]->GetPosition());
	}
}
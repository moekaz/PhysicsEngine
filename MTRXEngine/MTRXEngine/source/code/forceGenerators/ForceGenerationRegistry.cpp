#include <PrecompiledHeader.h>
#include <forceGenerators/ForceGenerationRegistry.h>
#include <entities/Particle.h>

namespace MTRX
{
	ForceGenerationRegistry::ForceGenerationRegistry()
	{}

	ForceGenerationRegistry::~ForceGenerationRegistry()
	{}

	void ForceGenerationRegistry::RemoveForceGenerator(const IForceGenerator* forceGenerator) 
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			if (*iter == forceGenerator)
			{
				forceGenerators.erase(iter);
				break;
			}
		}
	}

	void ForceGenerationRegistry::UpdateForceGenerators(Particle* particle)
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			(*iter)->UpdateForces(*particle);
		}
	}
}
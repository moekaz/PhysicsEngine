#include <PrecompiledHeader.h>
#include <forceGenerators/ForceGenerationRegistry.h>
#include <entities/Particle.h>

namespace MTRX
{
	ForceGenerationRegistry::ForceGenerationRegistry(Particle* particle) : particle(particle)
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

	void ForceGenerationRegistry::UpdateForceGenerators()
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			(*iter)->UpdateForces(*particle);
		}
	}
}
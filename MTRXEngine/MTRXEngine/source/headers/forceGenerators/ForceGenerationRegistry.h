/*
	Author: Mohamed Kazma
	Description: Allows us to have an API for force generators
*/

#pragma once

#include <forceGenerators/IForceGenerator.h>

namespace MTRX
{
	// Forward declarations
	class Particle;

	class ForceGenerationRegistry
	{
	public:
		Particle* particle;

		ForceGenerationRegistry(Particle* particle);
		~ForceGenerationRegistry();

		// Add a force generator to a particle's registry
		inline void AddForceGenerator(IForceGenerator* forceGenerator) { forceGenerators.push_back(forceGenerator); }
		// Remove a force generator from a particle's registry
		inline void RemoveForceGenerator(const int index) { forceGenerators.erase(forceGenerators.begin() + index); }
		// Remove by force generator
		void RemoveForceGenerator(const IForceGenerator* forceGenerator); // Remove a specific force generator
		// Removes All the force generators that we have
		inline void clearForceGenerators() { forceGenerators.clear(); }
		// Update the force generators
		void UpdateForceGenerators();

	private:
		std::vector<IForceGenerator*> forceGenerators; // The force generators that we going to be using
	};
}


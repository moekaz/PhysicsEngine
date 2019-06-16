/*
	Author: Mohamed Kazma
	Description: Some definitions that are useful
*/

#pragma once

namespace mtrx
{	
	#define LOGGER_FILE_SIZE 5242880 // Maximum size of logger file 
	
	enum class ColliderType : char { Sphere, Box, Capsule, Mesh, ConvexShape, };	// Type of what a collider is 
	static const float pi = 3.14159265358f;	// The value of pi (close enough)
	static float gravity = 30.f; // Constant value for gravity (not realistic value but games don't have realistic gravity)
	static const char* projectDir = (char*)std::filesystem::current_path().c_str(); // Gives us the project dir
	static glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	static glm::vec3 worldSide = glm::vec3(1.f, 0.f, 0.f);
	static glm::vec3 worldForward = glm::vec3(0.f, 0.f, -1.f);

	// Struct that holds some information about a spring
	struct SpringData
	{
		float stiffness;
		float restLength;

		SpringData(float stiffness, float restLength) : stiffness(stiffness), restLength(restLength) {}
	};

	// Struct that holds properties of a liquid used in the buoyancy generator
	struct LiquidProperties
	{
		float density;
		float volume;

		LiquidProperties(float density, float volume) : density(density), volume(volume) {}
	};

	// Transform struct that holds position orientation and scale
	struct Transform
	{
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 scale;
		
		Transform(const glm::vec3& position, const glm::quat& quaternion, const glm::vec3& scale) : position(position), orientation(quaternion), scale(scale) 
		{}
	};

	// Not sure whether this correct??
	static glm::mat3 GenerateCuboidIT(float mass, float* extents)
	{
		return glm::mat3(glm::vec3(0.08333f * mass * (extents[1] * extents[1] + extents[2] * extents[2])), 
			glm::vec3(0.08333f * mass * (extents[0] * extents[0] + extents[2] * extents[2])),
			glm::vec3(0.08333f * mass * (extents[0] * extents[0] + extents[1] * extents[1])));
	}
}

/*
	Author: Mohamed Kazma
	Description: Some definitions that are useful
*/

// DO I WANT THIS IN MY NAMESPACE???
#pragma once

#define LOGGER_FILE_SIZE 5242880 // Maximum size of logger file 
enum class ColliderType: char { Sphere, Box, Capsule, Mesh, ConvexShape, };	// Type of what a collider is 
const double pi = 3.14159265358;	// The value of pi (close enough)
float g = 15.f; // Constant value for gravity (not realistic value but games don't have realistic gravity)

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
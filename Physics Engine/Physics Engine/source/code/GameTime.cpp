/*
	Author: Mohamed Kazma
	Description: Some calculations of the game's time
*/

#include "../headers/GameTime.h"

// Setup the main values needed 
static const float startTime = time(0);
static float currentTime = startTime;
static float prevCurrentTime = NULL;

// Update 
void GameTime::Update()
{
	// Set the previous to the current
	prevCurrentTime = currentTime;
	// Get the current time
	currentTime = GameTime::GetTime();
	// Calculate delta time
	CalculateDeltaTime();
}

// Get the current time
float GameTime::GetCurrentTime()
{
	return currentTime;
}

// Get the start time of the application (mostly for loggin and stuff like that)
float GameTime::GetStartTime()
{
	return startTime;
}

// Gets what time it is right now
float GameTime::GetTime()
{
	return time(0);
}

// Calculate delta time
void GameTime::CalculateDeltaTime()
{
	deltaTime = currentTime - prevCurrentTime;
}

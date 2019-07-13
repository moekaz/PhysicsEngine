#pragma once

#include <log/LogManager.h>
#include <SimpleRenderer.h>
#include <Window.h>
#include <RigidbodyManager.h>
#include <ParticleManager.h>

class App
{
public:
	Window window;
	SimpleRenderer renderer;
	std::vector<mtrx::Transform*> transformsToRender;

	// Physics entity managers
	mtrx::RigidbodyManager rbManager;
	mtrx::ParticleManager pManager;
	
	bool cursor = false;

	void Update();
	void BaseInputCheck();

	App(const char* appName = "DEMO APPLICATION", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
	~App();
};
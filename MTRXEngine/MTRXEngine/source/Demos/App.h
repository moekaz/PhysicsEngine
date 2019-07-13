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
	std::unordered_set<mtrx::Transform*> transformsToRender;

	// Physics entity managers
	mtrx::RigidbodyManager rbManager;
	mtrx::ParticleManager pManager;
	bool cursor = false;

	App(const char* appName = "DEMO APPLICATION", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
	~App();

	void BaseInputCheck();
	virtual void InputCheck() = 0;
	virtual void Update();
	void Run();
};
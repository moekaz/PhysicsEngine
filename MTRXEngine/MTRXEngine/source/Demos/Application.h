#pragma once

#include <log/LogManager.h>
#include <SimpleRenderer.h>
#include <Window.h>

class Application
{
public:
	Window window;
	SimpleRenderer renderer;
	std::vector<mtrx::Transform*> transformsToRender;

	Application(const char* appName = "DEMO APPLICATION", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
	~Application();
};
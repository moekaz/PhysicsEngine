#include <PrecompiledHeader.h>
#include <Application.h>

Application::Application(const char* appName, int width, int height) : window(appName, width, height), renderer(window)
{
	mtrx::LogManager::init();
}

Application::~Application()
{}
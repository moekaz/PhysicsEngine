#include <PrecompiledHeader.h>
#include <log/LogManager.h>
#include <Window.h>

int main()
{
	mtrx::LogManager::init(); // Initialize the logger

	Window window = Window("DEMO WINDOW", 800, 600); 

	window.Update();

	return 0;
}
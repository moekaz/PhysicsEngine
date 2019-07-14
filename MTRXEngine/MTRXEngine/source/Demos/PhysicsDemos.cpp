#include <PrecompiledHeader.h>

#define DEMO 1

#if DEMO == 1
	#include <../Demos/ProjectileDemo.h>
#elif DEMO == 2
	#include <../Demos/CollisionDemo.h>
#endif

int main()
{
	// Initialize logger 
	mtrx::LogManager::init();

	// Demo application that we want to run
	std::unique_ptr<App> app;
#if DEMO == 1
	app = std::make_unique<ProjectileDemo>();
#elif DEMO == 2
	app = std::make_unique<CollisionDemo>();
#endif

	// Run application
	app->Run();

	return 0;
}

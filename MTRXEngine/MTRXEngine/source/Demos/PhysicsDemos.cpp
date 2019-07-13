#include <PrecompiledHeader.h>

#define DEMO 1

#if DEMO == 1
	#include <../Demos/ProjectileDemo.h>
#elif DEMO == 2
	#include <../Demos/CollisionDemo.h>
#endif

int main()
{
	// Demo application that we want to run
	std::shared_ptr<App> app;
#if DEMO == 1
	app = std::make_shared<ProjectileDemo>();
#elif DEMO == 2
	app = std::make_shared<CollisionDemo>();
#endif

	// Run application
	app->Run();

	return 0;
}

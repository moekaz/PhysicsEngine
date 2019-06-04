#include <PrecompiledHeader.h>
#include <log/LogManager.h>
#include <Window.h>
#include <SimpleRenderer.h>
#include <Transform.h>

int main()
{
	mtrx::LogManager::init(); // Initialize the logger

	Window window = Window("DEMO WINDOW", 800, 600);
	SimpleRenderer renderer = SimpleRenderer(&window);

	std::vector<Transform> transformsToRender;
	float angle = 0.0f;
	glm::quat orientation = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	transformsToRender.push_back(Transform(glm::vec3(0.0f, 0.0f, 0.0f), orientation, glm::vec3(1.0f, 1.0f, 1.0f)));

	while (!window.ShouldClose())
	{
		// Check for input
		window.InputCheck();

		// Clear the window
		window.Clear();

		// Render
		transformsToRender[0].orientation = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
		renderer.Render(transformsToRender);
		angle += 0.01f;

		// Clear buffers and poll
		window.UpdateBuffers();
	}

	return 0;
}

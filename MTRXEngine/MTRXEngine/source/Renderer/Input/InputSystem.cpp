#include <PrecompiledHeader.h>
#include <../Renderer/Input/InputSystem.h>

InputSystem::InputSystem(Window* window) :
	window(window)
{
	// Initialize keys and mouse buttons values
	memset(keys, 0, sizeof(char) * MAX_KEYS);
	memset(mouseButtons, 0, sizeof(char) * MAX_MOUSE_BUTTONS);

	// Setup key callback
	glfwSetKeyCallback(window->GetWindow(), KeyPressedCallback);

	// Cursor position callback
	glfwSetCursorPosCallback(window->GetWindow(), CursorPositionCallback);

	// Mouse button callback
	glfwSetMouseButtonCallback(window->GetWindow(), MouseButtonPressedCallback);

	// Scroll callback
	glfwSetScrollCallback(window->GetWindow(), ScrollCallback);

	// Cursor enter callback
	glfwSetCursorEnterCallback(window->GetWindow(), CursorEnterCallback);

	// Get cursor position
	double x, y;
	glfwGetCursorPos(window->GetWindow(), &x, &y);

	mousePosition.x = (float)x;
	mousePosition.y = (float)y;

	// Get rid of the cursor
	ToggleCursor(false);
}

void InputSystem::Update()
{
	mouseOffset.x = mouseOffset.y = 0;

	// TBD: Find a better solution
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == GLFW_PRESS)
			keys[i] = GLFW_REPEAT;
	}
}

void InputSystem::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputSystem::GetInstance(nullptr)->keys[key] = action;
}

void InputSystem::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputSystem* input = InputSystem::GetInstance(nullptr);
	input->mouseOffset.x = (float)xpos - input->mousePosition.x;
	input->mouseOffset.y = input->mousePosition.y - (float)ypos;
	input->mousePosition.x = (float)xpos;
	input->mousePosition.y = (float)ypos;
}

void InputSystem::MouseButtonPressedCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		// Mouse button pressed or held
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
			{
				break;
			}
			case GLFW_MOUSE_BUTTON_RIGHT:
			{
				break;
			}
		}
	}
	else
	{
		// Mouse button was released
	}
}

void InputSystem::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{

}

void InputSystem::CursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered == 1)
	{
		// Cursor entered window area
	}
	else
	{
		// Cursor left the window area
	}
}

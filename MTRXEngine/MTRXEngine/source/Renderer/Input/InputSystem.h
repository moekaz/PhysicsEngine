#pragma once

class InputSystem
{
public:
	inline bool GetKey(char keyCode) { return glfwGetKey(window, keyCode) != GLFW_RELEASE; }
	inline bool GetKeyDown(char keyCode) { return glfwGetKey(window, keyCode) == GLFW_PRESS; }
};


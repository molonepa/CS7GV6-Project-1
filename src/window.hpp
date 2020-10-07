#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	virtual ~Window();

private:
	GLFWwindow* window;
};

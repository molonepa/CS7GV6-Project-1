#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	virtual ~Window();

	void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void update();

	inline bool isOpen() { return p_isOpen; }

private:
	GLFWwindow* p_window;
	bool p_isOpen;
};

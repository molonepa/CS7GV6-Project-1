#include "window.hpp"
#include <stdexcept>

Window::Window(int width, int height, const std::string& title) {
	// initialise GLFW
	if (!glfwInit()) {
		throw std::runtime_error("ERROR: failed to initialise GLFW");
	}

	// initialise GLFW window
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL) {
		throw std::runtime_error("ERROR: failed to initialise GLFW window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
}

Window::~Window() {
	glfwTerminate();
}

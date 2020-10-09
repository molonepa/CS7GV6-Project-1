//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>

#include "../src/window.hpp"

#include <stdio.h>
//#include <stdexcept>
#include <vector>

int main() {
	Window window(1280, 720, "Hello");

	while (window.isOpen()) {
		window.update();
	}
	return 0;
}

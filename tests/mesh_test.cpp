#include "../src/window.hpp"
#include "../src/mesh.hpp"
#include "../src/vertex.hpp"

#include <stdio.h>
#include <vector>

int main() {
	Window window(1280, 720, "Hello");

	while (window.isOpen()) {
		window.update();
	}

	return 0;
}

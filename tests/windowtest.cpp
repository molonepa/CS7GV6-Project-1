#include "../src/window.hpp"
#include <cmath>

int main() {
	Window window(1280, 720, "Hello");

	float r, g, b = 0.0f;

	float count = 0.0f;
	while (window.isOpen()) {
		window.clear(r, g, b, 1.0f);
		window.update();
		r = sin(count);
		g = sin(3*count);
		b = -sin(count+0.5f);
		count += 0.0005f;
	}

	return 0;
}

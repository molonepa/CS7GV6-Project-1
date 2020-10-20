#include "../src/window.hpp"
#include "../src/mesh.hpp"
#include "../src/vertex.hpp"
#include "../src/shader.hpp"
#include "../src/texture.hpp"

#include <stdio.h>
#include <vector>

int main() {
	Window window(1280, 720, "Hello");

	Shader shader("src/shaders/test_texture");

	Mesh boat = Mesh("data/models/boat.obj");

	Texture texture("data/textures/Fishing boat 1.png");

	while (window.isOpen()) {
		window.clear(0.5f, 0.5f, 0.5f, 1.0f);
		shader.bind();
		texture.bind(0);
		boat.render(GL_TRIANGLES);
		window.update();
	}

	return 0;
}

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

	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)));
	vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0)));
	std::vector<int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	Mesh triangle = Mesh(vertices, indices);

	Texture texture("./data/textures/Fishing boat 1.png");

	while (window.isOpen()) {
		window.clear(0.5f, 0.5f, 0.5f, 1.0f);
		shader.bind();
		texture.bind(0);
		triangle.render(GL_TRIANGLES);
		window.update();
	}

	return 0;
}

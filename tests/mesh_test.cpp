#include "../src/window.hpp"
#include "../src/mesh.hpp"
#include "../src/shader.hpp"
#include "../src/utils/vertex.hpp"

#include <stdio.h>
#include <vector>

int main() {
	Window window(1280, 720, "Hello");
	Shader shader = Shader("tests/test_shaders/mesh_test");

	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.0, 0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.0)));
	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	Mesh triangle = Mesh(vertices, indices);
	Mesh boat = Mesh("data/models/boat.obj");

	while (window.isOpen()) {
		window.clear();
		shader.bind();
		triangle.render();
		boat.render();
		window.update();
	}

	return 0;
}

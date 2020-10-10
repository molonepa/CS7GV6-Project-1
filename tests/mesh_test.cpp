#include "../src/window.hpp"
#include "../src/mesh.hpp"
#include "../src/vertex.hpp"

#include <stdio.h>
#include <vector>

int main() {
	Window window(1280, 720, "Hello");

	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.0, 0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.0)));

	Mesh triangle = Mesh(vertices, indices);

	while (window.isOpen()) {
		window.update();
	}

	return 0;
}

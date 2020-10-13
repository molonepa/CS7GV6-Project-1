#include "window.hpp"
#include "vertex.hpp"
#include "mesh.hpp"
#include "shader.hpp"

int main() {
	Window window(1280, 720, "Application");
	Shader defaultShader = Shader();

	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.0, 0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.0)));
	std::vector<int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	Mesh triangle = Mesh(vertices, indices);

	while (window.isOpen()) {
		window.clear(0.5f, 0.5f, 0.5f, 1.0f);
		defaultShader.bind();
		triangle.render(GL_TRIANGLES);
		window.update();
	}
	return 0;
}

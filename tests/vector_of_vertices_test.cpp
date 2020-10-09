#include "../src/vertex.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>

#include <glm/gtx/string_cast.hpp>

int main() {
	std::vector<Vertex> vertices;

	vertices.push_back(Vertex(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec2(4.0f, 5.0f), glm::vec3(6.0f, 7.0f, 8.0f)));
	vertices.push_back(Vertex(glm::vec3(11.0f, 12.0f, 13.0f), glm::vec2(14.0f, 15.0f), glm::vec3(16.0f, 17.0f, 18.0f)));
	vertices.push_back(Vertex(glm::vec3(21.0f, 22.0f, 23.0f), glm::vec2(24.0f, 25.0f), glm::vec3(26.0f, 27.0f, 28.0f)));

	for (std::size_t i = 0; i < vertices.size(); i++) {
		std::cout << "pos: " << glm::to_string(vertices[i].getPos()) << std::endl;
		std::cout << "texCoord: " << glm::to_string(vertices[i].getTexCoord()) << std::endl;
		std::cout << "normal: " << glm::to_string(vertices[i].getNormal()) << std::endl;
		std::cout << std::endl;
	}

	return 0;
}

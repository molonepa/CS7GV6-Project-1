#include "../src/vertex.hpp"

#include <stdio.h>
#include <iostream>

#include <glm/gtx/string_cast.hpp>

int main() {
	Vertex vert = Vertex(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec2(4.0f, 5.0f), glm::vec3(6.0f, 7.0f, 8.0f));

	std::cout << "pos: " << glm::to_string(vert.getPos()) << std::endl;
	std::cout << "texCoord: " << glm::to_string(vert.getTexCoord()) << std::endl;
	std::cout << "normal: " << glm::to_string(vert.getNormal()) << std::endl;

	return 0;
}

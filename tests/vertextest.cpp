#include "../src/utils/vertex.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

int main() {
	Vertex default_vert = Vertex();

	std::cout << "default values:" << std::endl;
	std::cout << "pos: " << glm::to_string(default_vert.getPos()) << std::endl;
	std::cout << "uv: " << glm::to_string(default_vert.getUV()) << std::endl;
	std::cout << "normal: " << glm::to_string(default_vert.getNormal()) << std::endl;

	Vertex custom_vert = Vertex(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec2(4.0f, 5.0f), glm::vec3(6.0f, 7.0f, 8.0f));

	std::cout << "custom values:" << std::endl;
	std::cout << "pos: " << glm::to_string(custom_vert.getPos()) << std::endl;
	std::cout << "uv: " << glm::to_string(custom_vert.getUV()) << std::endl;
	std::cout << "normal: " << glm::to_string(custom_vert.getNormal()) << std::endl;

	return 0;
}

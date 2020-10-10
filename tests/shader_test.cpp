#include "../src/window.hpp"
#include "../src/shader.hpp"

#include <stdio.h>
#include <vector>

int main() {
	Window window(1280, 720, "Hello");

	Shader defaultShader();

	std::vector<glm::vec3> positions;
	positions.push_back(glm::vec3(-0.75f, -0.75f, 0.0f));
	positions.push_back(glm::vec3(0.25f, -0.75f, 0.0f));
	positions.push_back(glm::vec3(-0.25f, 0.25f, 0.0f));
	positions.push_back(glm::vec3(-0.25f, 0.75f, 0.0f));
	positions.push_back(glm::vec3(0.75f, 0.75f, 0.0f));
	positions.push_back(glm::vec3(0.25f, -0.25f, 0.0f));

	std::vector<glm::vec4> colours;
	colours.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colours.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colours.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	colours.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	colours.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	colours.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	while (window.isOpen()) {
		window.update();
	}
	return 0;
}

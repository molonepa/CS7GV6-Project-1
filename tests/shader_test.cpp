#include "../src/window.hpp"
#include "../src/shader.hpp"

#include <glm/glm.hpp>

#include <stdio.h>
#include <vector>

GLuint createVertexArrayObject() {
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	return VAO;
}

void createVertexBufferObject(std::vector<glm::vec3> positions, std::vector<glm::vec4> colours) {
	enum {
		POSITION_VB,
		COLOUR_VB,
		NUM_BUFFERS
	};
	GLuint VBO[NUM_BUFFERS];
	glGenBuffers(NUM_BUFFERS, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours[0]) * colours.size(), &colours[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

int main() {
	Window window(1280, 720, "Hello");

	Shader testShader("src/shaders/test");

	GLuint VAO = createVertexArrayObject();

	std::vector<glm::vec3> positions;
	positions.push_back(glm::vec3(-0.75f, -0.75f, 0.0f));
	positions.push_back(glm::vec3(0.25f, -0.75f, 0.0f));
	positions.push_back(glm::vec3(-0.25f, 0.25f, 0.0f));
	std::vector<glm::vec4> colours;
	colours.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colours.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colours.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	createVertexBufferObject(positions, colours);

	while (window.isOpen()) {
		window.clear(0.5f, 0.5f, 0.5f, 1.0f);
		testShader.bind();
		glDrawArrays(GL_TRIANGLES, 0, positions.size());
		window.update();
	}
	return 0;
}

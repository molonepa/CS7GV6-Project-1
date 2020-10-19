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

	bool u_bool = true;
	int u_int = 1;
	float u_float = 1.0f;
	float u_double = 1.0d;
	glm::vec2 u_vec2 = glm::vec2(0.0f);
	glm::vec3 u_vec3 = glm::vec3(0.0f);
	glm::vec4 u_vec4 = glm::vec4(0.0f);
	glm::mat3 u_mat3 = glm::mat3(0.0f);
	glm::mat4 u_mat4 = glm::mat4(0.0f);

	while (window.isOpen()) {
		window.clear(0.5f, 0.5f, 0.5f, 1.0f);

		testShader.updateUniform("u_bool", u_bool);
		testShader.updateUniform("u_int", u_int);
		testShader.updateUniform("u_float", u_float);
		testShader.updateUniform("u_double", u_double);
		testShader.updateUniform("u_vec2", u_vec2);
		testShader.updateUniform("u_vec3", u_vec3);
		testShader.updateUniform("u_vec4", u_vec4);
		testShader.updateUniform("u_mat3", u_mat3);
		testShader.updateUniform("u_mat4", u_mat4);
		testShader.bind();

		glDrawArrays(GL_TRIANGLES, 0, positions.size());
		window.update();
	}
	return 0;
}

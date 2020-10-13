#include "../src/window.hpp"
#include "../src/mesh.hpp"
#include "../src/vertex.hpp"

#include <stdio.h>
#include <vector>

const char* vertex_shader =
	"#version 400\n"
	"in vec3 vert_position;"
	"in vec2 vert_uv;"
	"in vec3 vert_normal;"
	"out vec4 colour;"
	"void main() {"
	"	gl_Position = vec4(vert_position, 1.0);"
	"	colour = vec4(0.0, 1.0, 0.0, 1.0);"
	"}";

const char* fragment_shader =
	"#version 400\n"
	"in vec4 colour;"
	"out vec4 frag_colour;"
	"void main() {"
	"	frag_colour = colour;"
	"}";

GLuint compileAndLoadShaders(const char* vertex_shader, const char* fragment_shader) {
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint prog_id = glCreateProgram();
	glAttachShader(prog_id, fs);
	glAttachShader(prog_id, vs);
	glLinkProgram(prog_id);

	glUseProgram(prog_id);

	return prog_id;
}

int main() {
	Window window(1280, 720, "Hello");

	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.0, 0.5, 0.0)));
	vertices.push_back(Vertex(glm::vec3(0.5, -0.5, 0.0)));
	std::vector<int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	Mesh triangle = Mesh(vertices, indices);

	GLuint shader_program_id = compileAndLoadShaders(vertex_shader, fragment_shader);

	while (window.isOpen()) {
		window.clear(0.5f, 0.5f, 0.5f, 1.0f);
		triangle.render(GL_TRIANGLES);
		window.update();
	}

	return 0;
}

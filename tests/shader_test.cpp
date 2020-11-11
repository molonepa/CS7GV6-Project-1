#include "../src/utils/window_manager.hpp"
#include "../src/utils/shader.hpp"

#include <glm/glm.hpp>

#include <stdio.h>
#include <vector>

int main() {
	WindowManager window(1280, 720, "Hello");

	Shader testShader("tests/test_shaders/shader_test");

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
		window.clear();

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

		window.update();
	}
	return 0;
}

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

class Shader {
public:
	Shader(const std::string& filename = "src/shaders/default");
	virtual ~Shader();

	void bind();

	//void addInput(int pos, std::string attributeName);

	void updateUniform(std::string name, const bool u);
	void updateUniform(std::string name, const int u);
	void updateUniform(std::string name, const float u);
	void updateUniform(std::string name, const double u);
	void updateUniform(std::string name, const glm::vec2 u);
	void updateUniform(std::string name, const glm::vec3 u);
	void updateUniform(std::string name, const glm::vec4 u);
	void updateUniform(std::string name, const glm::mat3 u);
	void updateUniform(std::string name, const glm::mat4 u);

private:
	static const unsigned int p_NUM_SHADERS = 2;

	GLuint p_shaderID;
	GLuint p_shaderPrograms[p_NUM_SHADERS];
};

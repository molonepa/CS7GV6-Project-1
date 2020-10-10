#pragma once

#include <GL/glew.h>

#include <string>

class Shader {
public:
	Shader(const std::string& filename = "shaders/default/deafult_shader");
	virtual ~Shader();

	void bind();

private:
	const unsigned int p_NUM_SHADERS = 2;

	GLuint p_shaderID;
	GLuint p_shaderPrograms[NUM_SHADERS];
};

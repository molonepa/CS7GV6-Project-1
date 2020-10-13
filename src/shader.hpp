#pragma once

#include <GL/glew.h>

#include <string>

class Shader {
public:
	Shader(const std::string& filename = "src/shaders/default");
	virtual ~Shader();

	void bind();

private:
	static const unsigned int p_NUM_SHADERS = 2;

	GLuint p_shaderID;
	GLuint p_shaderPrograms[p_NUM_SHADERS];
};

#include "shader.hpp"

void checkShaderError(GLuint shaderID, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = {0};

	if (isProgram) {
		glGetProgramiv(shaderID, flag, &success);
	}
	else {
		glGetShaderiv(shaderID, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shaderID, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shaderID, sizeof(error), NULL, error);
		}

		std::cout << error << std::endl;
		throw std::runtime_error(errorMessage);
	}
}

GLuint compileShaderSource(const std::string& text, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType);

	if (shaderID == 0) {
		throw std::runtime_error("ERROR: Failed to create shader");
	}

	const GLchar* shaderSource[1];
	GLint shaderSourceLen[1];

	shaderSource[0] = text.c_str();
	shaderSourceLen[0] = text.length();

	glShaderSource(shaderID, 1, shaderSource, shaderSourceLen);
	glCompileShader(shaderID);

	checkShaderError(shaderID, GL_COMPILE_STATUS, false, "ERROR: Failed to compile shader source");

	return shaderID;
}

std::string loadShaderSource(const std::string& filename) {
	std::ifstream file;
	file.open((filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		throw std::runtime_error("ERROR: Failed to load shader source");
	}

	return output;
}

Shader::Shader(const std::string& filename) {
	p_shaderID = glCreateProgram();

	p_shaderPrograms[0] = compileShaderSource(loadShaderSource(filename + ".vs"), GL_VERTEX_SHADER);
	p_shaderPrograms[1] = compileShaderSource(loadShaderSource(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < p_NUM_SHADERS; i++) {
		glAttachShader(p_shaderID, p_shaderPrograms[i]);
	}

	glLinkProgram(p_shaderID);
	checkShaderError(p_shaderID, GL_LINK_STATUS, true, "ERROR: Failed to link shader program");

	glValidateProgram(p_shaderID);
	checkShaderError(p_shaderID, GL_VALIDATE_STATUS, true, "ERROR: Failed to validate shader program");
}

Shader::~Shader() {
	for (unsigned int i = 0; i < p_NUM_SHADERS; i++) {
		glDetachShader(p_shaderID, p_shaderPrograms[i]);
		glDeleteShader(p_shaderPrograms[i]);
	}

	glDeleteProgram(p_shaderID);
}

void Shader::bind() {
	glUseProgram(p_shaderID);
}

void Shader::updateUniform(std::string name, const bool u) {
	glUniform1i(glGetUniformLocation(p_shaderID, name.c_str()), u);
}

void Shader::updateUniform(std::string name, const int u) {
	glUniform1i(glGetUniformLocation(p_shaderID, name.c_str()), u);
}

void Shader::updateUniform(std::string name, const float u) {
	glUniform1f(glGetUniformLocation(p_shaderID, name.c_str()), u);
}

void Shader::updateUniform(std::string name, const double u) {
	glUniform1f(glGetUniformLocation(p_shaderID, name.c_str()), (float)u);
}

void Shader::updateUniform(std::string name, const glm::vec2 u) {
	glUniform2fv(glGetUniformLocation(p_shaderID, name.c_str()), 1, &u[0]);
}

void Shader::updateUniform(std::string name, const glm::vec3 u) {
	glUniform3fv(glGetUniformLocation(p_shaderID, name.c_str()), 1, &u[0]);
}

void Shader::updateUniform(std::string name, const glm::vec4 u) {
	glUniform3fv(glGetUniformLocation(p_shaderID, name.c_str()), 1, &u[0]);
}

void Shader::updateUniform(std::string name, const glm::mat3 u) {
	glUniformMatrix3fv(glGetUniformLocation(p_shaderID, name.c_str()), 1, GL_FALSE, &u[0][0]);
}

void Shader::updateUniform(std::string name, const glm::mat4 u) {
	glUniformMatrix4fv(glGetUniformLocation(p_shaderID, name.c_str()), 1, GL_FALSE, &u[0][0]);
}

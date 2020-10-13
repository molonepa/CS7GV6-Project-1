#pragma once

#include "vertex.hpp"
#include <GL/glew.h>

#include <vector>

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
	virtual ~Mesh();

	void render(GLenum mode);

private:
	void initialiseMeshFromVectors(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<int> indices);

	enum {
		p_POSITION_VB,
		p_UV_VB,
		p_NORMAL_VB,
		p_INDEX_VB,
		p_NUM_BUFFERS
	};

	GLuint p_VAO;
	GLuint p_VBO[p_NUM_BUFFERS];

	unsigned int p_drawCount;
};

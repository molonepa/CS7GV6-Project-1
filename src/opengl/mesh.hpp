#pragma once

#include "../utils/vertex.hpp"
#include "../utils/obj_loader.hpp"

#include <GL/glew.h>

#include <vector>

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(const std::string& filename = "data/models/default_cube.obj");
	virtual ~Mesh();

	void render(GLenum mode = GL_TRIANGLES);

	//void renderInstances(GLenum mode, int numInstances);

private:
	void generateVertexBuffers(const IndexedModel& indexedModel);

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

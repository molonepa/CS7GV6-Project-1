#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	IndexedModel indexedModel;

	for (std::size_t i = 0; i < vertices.size(); i++) {
		indexedModel.positions.push_back(vertices[i].getPos());
		indexedModel.uvs.push_back(vertices[i].getUV());
		indexedModel.normals.push_back(vertices[i].getNormal());
	}

	generateVertexBuffers(indexedModel);
}

Mesh::Mesh(const std::string& filename) {
	OBJModel objModel = OBJModel(filename);
	IndexedModel indexedModel = objModel.ToIndexedModel();

	generateVertexBuffers(indexedModel);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &p_VAO);
}

void Mesh::render(GLenum mode) {
	glBindVertexArray(p_VAO);
	glDrawElements(mode, p_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::generateVertexBuffers(const IndexedModel& indexedModel) {
	p_drawCount = indexedModel.indices.size();

	glGenVertexArrays(1, &p_VAO);
	glBindVertexArray(p_VAO);

	glGenBuffers(p_NUM_BUFFERS, p_VBO);

	// push vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, p_VBO[p_POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, indexedModel.positions.size() * sizeof(indexedModel.positions[0]), &indexedModel.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// push vertex uvs
	glBindBuffer(GL_ARRAY_BUFFER, p_VBO[p_UV_VB]);
	glBufferData(GL_ARRAY_BUFFER, indexedModel.uvs.size() * sizeof(indexedModel.uvs[0]), &indexedModel.uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// push vertex normals
	glBindBuffer(GL_ARRAY_BUFFER, p_VBO[p_NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, indexedModel.normals.size() * sizeof(indexedModel.normals[0]), &indexedModel.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// push indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_VBO[p_INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexedModel.indices.size() * sizeof(indexedModel.indices[0]), &indexedModel.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

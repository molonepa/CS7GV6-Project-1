#include <mesh.hpp>

#include <vector>

Model::Model(std::vector<Vertex> vertices, std::vector<int> indices) {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	for (std::size_t i = 0; i < vertices.size(); i++) {
		positions.push_back(vertices[i].getPos());
		uvs.push_back(vertices[i].getTexCoord());
		normals.push_back(vertices[i].getNormal());
	}

	initialiseMeshFromVectors(positions, uvs, normals, indices);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::render() {
	glBindVertexArray(p_VAO);
	glDrawElements(mode, p_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::initialiseMeshFromVectors(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<int> indices) {
	p_drawCount = indices.size();

	glGenVertexArrays(1, &p_VAO);
	glBindVertexArray(p_VAO);

	glGenBuffers(p_NUM_BUFFERS, p_VBO);

	// push vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, p_VBO[p_POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// push vertex uvs
	glBindBuffer(GL_ARRAY_BUFFER, p_VBO[p_UV_VB]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// push vertex normals
	glBindBuffer(GL_ARRAY_BUFFER, p_VBO[p_NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// push indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_VBO[p_INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

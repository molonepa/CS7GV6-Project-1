#pragma once

#include <glm/glm.hpp>

class Vertex {
public:
	Vertex(const glm::vec3& pos = glm::vec3(0.0), const glm::vec2& uv = glm::vec2(0.0), const glm::vec3& normal = glm::vec3(0.0)) {
		this->p_pos = pos;
		this->p_uv = uv;
		this->p_normal = normal;
	}

	// getters
	inline glm::vec3 getPos() { return p_pos; }
	inline glm::vec2 getUV() { return p_uv; }
	inline glm::vec3 getNormal() { return p_normal; }

private:
	glm::vec3 p_pos;
	glm::vec2 p_uv;
	glm::vec3 p_normal;
};

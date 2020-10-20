#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
public:
	Transform(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f)) {
		this->p_position = position;
		this->p_rotation = rotation;
		this->p_scale = scale;
	}

	inline glm::vec3 getPosition() { return p_position; }
	inline glm::vec3 getRotation() { return p_rotation; }
	inline glm::vec3 getScale() { return p_scale; }

	inline void setPosition(glm::vec3 p) { p_position = p; }
	inline void setRotation(glm::vec3 r) { p_rotation = r; }
	inline void setScale(glm::vec3 s) { p_scale = s; }

	inline glm::mat4 getModelMatrix() const {
		glm::mat4 posMatrix = glm::translate(p_position);

		glm::mat4 rotXMatrix = glm::rotate(p_rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(p_rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(p_rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		glm::mat4 scaleMatrix = glm::scale(p_scale);

		return posMatrix * rotMatrix * scaleMatrix;
	}

private:
	glm::vec3 p_position;
	glm::vec3 p_rotation;
	glm::vec3 p_scale;
};

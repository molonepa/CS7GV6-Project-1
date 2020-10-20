#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(const glm::vec3& position, float fov, float aspect, float zNear, float zFar) {
		this->p_position = position;
		this->p_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		this->p_up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->p_perspective = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 getViewProjectionMatrix() const {
		return p_perspective * glm::lookAt(p_position, p_position + p_forward, p_up);
	}

private:
	glm::vec3 p_position;
	glm::vec3 p_forward;
	glm::vec3 p_up;
	glm::mat4 p_perspective;
};

#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	Camera(const glm::vec3& position = glm::vec3(0.0f), float fov = 70.0f, float aspect = 1.77777f, float zNear = 0.1f, float zFar = 100.0f) {
		this->p_position = position;
		this->p_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		this->p_up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->p_perspective = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 getViewProjectionMatrix() const {
		return p_perspective * glm::lookAt(p_position, p_position + p_forward, p_up);
	}

	inline glm::vec3 getForward() { return p_forward; }

private:
	glm::vec3 p_position;
	glm::vec3 p_forward;
	glm::vec3 p_up;
	glm::mat4 p_perspective;
};

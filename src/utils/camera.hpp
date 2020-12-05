#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

class Camera {
public:
	Camera(const glm::vec3& position = glm::vec3(0.0f), float fov = 70.0f, float aspect = 1.77777f, float zNear = 0.1f, float zFar = 500000.0f, float sensitivity = 0.4f) {
		p_position = position;
		p_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		p_up = glm::vec3(0.0f, 1.0f, 0.0f);
		p_yaw = -90.0f;
		p_pitch = 0.0f;
		p_sensitivity = sensitivity;
		p_zNear = zNear;
		p_zFar = zFar;
		p_projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 getViewProjectionMatrix() {
		if (!p_mapMode) {
			return p_projection * glm::lookAt(p_position, p_position + p_forward, p_up);
		}
		else {
			p_position = glm::vec3(0.0f, 500.0f, 0.0f);
			return glm::ortho(-5000.0f, 5000.0f, -5000.0f, 5000.0f, p_zNear, p_zFar) * glm::lookAt(glm::vec3(0.0f, 500.0f, 0.0f), glm::vec3(0.0f, 500.0f, 0.0f) + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}

	inline void update(glm::vec3 position) {
		p_position = position;
		deactivateMapMode();
	}

	inline glm::vec3 getPosition() { return p_position; }

	inline void turn(int deltaX, int deltaY) {
		if (!p_mapMode) {
			glm::vec3 front;

			p_yaw += deltaX * p_sensitivity;
			p_pitch -= deltaY * p_sensitivity;

			if (p_pitch > 89.0f) {
				p_pitch = 89.0f;
			}
			if (p_pitch < -89.0f) {
				p_pitch = -89.0f;
			}

			front.x = std::cos(glm::radians(p_yaw)) * std::cos(glm::radians(p_pitch));
			front.y = std::sin(glm::radians(p_pitch));
			front.z = std::sin(glm::radians(p_yaw)) * std::cos(glm::radians(p_pitch));

			p_forward = glm::normalize(front);
		};
	}

	inline void activateMapMode() {
		p_mapMode = true;
	}

	inline void deactivateMapMode() {
		p_mapMode = false;
	}

private:
	glm::vec3 p_position;

	glm::vec3 p_forward;
	glm::vec3 p_up;

	glm::mat4 p_projection;
	float p_zNear;
	float p_zFar;

	float p_yaw;
	float p_pitch;
	float p_sensitivity;

	enum p_projections {
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	bool p_mapMode = false;
};

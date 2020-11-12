#pragma once

#include "transform.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

class Camera {
public:
	Camera(const glm::vec3& position = glm::vec3(0.0f), float fov = 70.0f, float aspect = 1.77777f, float zNear = 0.1f, float zFar = 1000.0f) {
		//this->p_position = position;
		this->p_transform.setPosition(position);
		this->p_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		this->p_up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->p_perspective = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 getViewProjectionMatrix() {
		glm::vec3 position = p_transform.getPosition();
		return p_perspective * glm::lookAt(position, position + p_forward, p_up);
	}

	inline void lookUp() {
		glm::vec3 right = glm::cross(p_forward, p_up);
		glm::vec3 rotation = p_transform.getRotation();
		rotation += right * p_turnSpeed;
		p_transform.setRotation(rotation);

		// update forward vector
		p_forward = glm::normalize(glm::vec3(glm::inverse(p_transform.getModelMatrix())[2]));
		p_forward.z *= -1;

		// update up vector
		p_up = glm::cross(right, p_forward);
	}

	inline void lookDown() {
		glm::vec3 right = glm::cross(p_forward, p_up);
		glm::vec3 rotation = p_transform.getRotation();
		rotation -= right * p_turnSpeed;
		p_transform.setRotation(rotation);

		// update forward vector
		p_forward = glm::normalize(glm::vec3(glm::inverse(p_transform.getModelMatrix())[2]));
		p_forward.z *= -1;

		// update up vector
		p_up = glm::cross(right, p_forward);
	}

	inline void lookLeft() {
		glm::vec3 rotation = p_transform.getRotation();
		rotation += p_up * p_turnSpeed;
		p_transform.setRotation(rotation);

		// update forward vector
		p_forward = glm::normalize(glm::vec3(glm::inverse(p_transform.getModelMatrix())[2]));
		p_forward.z *= -1;
	}

	inline void lookRight() {
		glm::vec3 rotation = p_transform.getRotation();
		rotation -= p_up * p_turnSpeed;
		p_transform.setRotation(rotation);

		// update forward vector
		p_forward = glm::normalize(glm::vec3(glm::inverse(p_transform.getModelMatrix())[2]));
		p_forward.z *= -1;
	}

private:
	//glm::vec3 p_position;
	Transform p_transform;
	glm::vec3 p_forward;
	glm::vec3 p_up;
	glm::mat4 p_perspective;
	const float p_turnSpeed = 0.05f;
};

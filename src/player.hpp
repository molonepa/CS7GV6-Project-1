#pragma once

#define PI 3.1415926353

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"

#include <glm/gtx/rotate_vector.hpp>

class Player {
public:
	inline void draw(Camera camera, Light light, const float& elapsedTime) {
		updateMovement(elapsedTime);

		p_shader.bind();
		p_shader.updateUniform("viewProjectionMatrix", camera.getViewProjectionMatrix());
		p_shader.updateUniform("camera_position", camera.getPosition());
		p_shader.updateUniform("light_colour", light.getColour());
		p_shader.updateUniform("light_position", light.getPosition());
		p_shader.updateUniform("ambient_strength", light.getStrength());
		p_shader.updateUniform("specular_strength", 0.3f);
		p_shader.updateUniform("reflection_strength", 0.3f);
		p_shader.updateUniform("modelMatrix", p_boatTransform.getModelMatrix() * p_motorTransform.getModelMatrix());

		p_motorTexture.bind(0);
		p_motorMesh.render();

		p_shader.updateUniform("modelMatrix", p_boatTransform.getModelMatrix());
		p_boatTexture.bind(0);
		p_boatMesh.render();
	}

	inline void updateMovement(const float& time) {
		if (!p_isMoving) {
			// decelerate due to friction
			p_currentSpeed -= 0.5 * p_acceleration;
			if (p_currentSpeed < 0.0f) {
				p_currentSpeed = 0.0f;
			}
		}

		glm::vec3 position = p_boatTransform.getPosition();
		position += p_currentSpeed * p_forward;
		position.y += 0.25 * sin(0.1 * time);
		p_boatTransform.setPosition(position);

		p_isMoving = false;
	}

	inline void moveForward() {
		p_isMoving = true;
		// rotate motor back to neutral position
		glm::vec3 rotation = p_motorTransform.getRotation();
		if (rotation.y > p_minTurnRotation) {
			rotation -= p_up * (2 * p_turnSpeed);
		}
		else if (rotation.y < p_minTurnRotation) {
			rotation += p_up * (2 * p_turnSpeed);
		}
		p_motorTransform.setRotation(rotation);

		p_currentSpeed += p_acceleration;
		if (p_currentSpeed > p_maxForwardsSpeed) {
			p_currentSpeed = p_maxForwardsSpeed;
		}
	}

	inline void moveBack() {
		p_isMoving = true;
		// rotate motor back to neutral position
		glm::vec3 rotation = p_motorTransform.getRotation();
		if (rotation.y > p_minTurnRotation) {
			rotation -= p_up * (2 * p_turnSpeed);
		}
		else if (rotation.y < p_minTurnRotation) {
			rotation += p_up * (2 * p_turnSpeed);
		}
		p_motorTransform.setRotation(rotation);

		p_currentSpeed -= p_acceleration;
		if (p_currentSpeed < p_maxBackwardsSpeed) {
			p_currentSpeed = p_maxBackwardsSpeed;
		}
	}

	inline void turnLeft() {
		// rotate motor left up to max rotation
		glm::vec3 rotation = p_motorTransform.getRotation();
		rotation -= p_up * p_turnSpeed;
		if (rotation.y < -p_maxTurnRotation) {
			rotation.y = -p_maxTurnRotation;
		}
		p_motorTransform.setRotation(rotation);

		// rotate boat left
		rotation = p_boatTransform.getRotation();
		rotation += p_up * p_turnSpeed;
		p_boatTransform.setRotation(rotation);

		// update forward vector
		p_forward = glm::normalize(glm::vec3(glm::inverse(p_boatTransform.getModelMatrix())[2]));
		p_forward.z *= -1;
	}

	inline void turnRight() {
		// rotate motor right up to max rotation
		glm::vec3 rotation = p_motorTransform.getRotation();
		rotation += p_up * p_turnSpeed;
		if (rotation.y > p_maxTurnRotation) {
			rotation.y = p_maxTurnRotation;
		}
		p_motorTransform.setRotation(rotation);

		// rotate boat right
		rotation = p_boatTransform.getRotation();
		rotation -= p_up * p_turnSpeed;
		p_boatTransform.setRotation(rotation);

		// update forward vector
		p_forward = glm::normalize(glm::vec3(glm::inverse(p_boatTransform.getModelMatrix())[2]));
		p_forward.z *= -1;
	}

	inline glm::vec3 getCameraPosition() {
		glm::vec3 position = p_boatTransform.getPosition();
		position += 5.0f * p_up;
		position -= 7.0f * p_forward;
		return position;
	}

	inline glm::vec3 getPosition() {
		return p_boatTransform.getPosition();
	}

	inline void addToCapacity(float weight) {
		if (p_currentCapacity < p_maxCapacity) {
			p_currentCapacity += weight;
		}
		if (p_currentCapacity > p_maxCapacity) {
			p_currentCapacity = p_maxCapacity;
		}
	}

	inline float getCurrentCapacity() {
		return p_currentCapacity;
	}

	inline float getMaxCapacity() {
		return p_maxCapacity;
	}

	inline bool isOverCapacity() {
		if (p_currentCapacity < p_maxCapacity) {
			return false;
		}
		else {
			return true;
		}
	}

private:
	Mesh p_boatMesh = Mesh("data/models/boat.obj");
	Texture p_boatTexture = Texture("data/textures/boat.png");
	Transform p_boatTransform = Transform(glm::vec3(0.0f, 0.0f, -1250.0f));

	Mesh p_motorMesh = Mesh("data/models/motor.obj");
	Texture p_motorTexture = Texture("data/textures/motor.png");
	Transform p_motorTransform = Transform(glm::vec3(0.0f, 0.0f, 17.296f));

	Shader p_shader;

	glm::vec3 p_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f);

	const float p_minTurnRotation = 0.0f;
	const float p_maxTurnRotation = 1.0f;

	const float p_acceleration = 0.1f;
	float p_currentSpeed = 0.0f;
	const float p_maxForwardsSpeed = 7.50f;
	const float p_maxBackwardsSpeed = -5.0f;
	const float p_turnSpeed = 0.02f;
	bool p_isMoving = false;

	float p_currentCapacity = 0.0f;
	float p_maxCapacity = 25.0f;
};

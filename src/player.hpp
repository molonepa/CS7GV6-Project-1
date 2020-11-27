#pragma once

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"

#include <glm/gtx/rotate_vector.hpp>

class Player {
public:
	inline void draw(Camera camera, Light light) {
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

	inline void moveForward() {
		// rotate motor back to neutral position
		glm::vec3 rotation = p_motorTransform.getRotation();
		if (rotation.y > p_minTurnRotation) {
			rotation -= p_up * (2 * p_turnSpeed);
		}
		else if (rotation.y < p_minTurnRotation) {
			rotation += p_up * (2 * p_turnSpeed);
		}
		p_motorTransform.setRotation(rotation);

		// update position at full speed
		glm::vec3 position = p_boatTransform.getPosition();
		   position += p_moveSpeed * p_forward;
		p_boatTransform.setPosition(position);
	}

	inline void moveBack() {
		// rotate motor back to neutral position
		glm::vec3 rotation = p_motorTransform.getRotation();
		if (rotation.y > p_minTurnRotation) {
			rotation -= p_up * (2 * p_turnSpeed);
		}
		else if (rotation.y < p_minTurnRotation) {
			rotation += p_up * (2 * p_turnSpeed);
		}
		p_motorTransform.setRotation(rotation);

		// update position at 0.25 * speed
		glm::vec3 position = p_boatTransform.getPosition();
		   position -= (0.25f * p_moveSpeed) * p_forward;
		p_boatTransform.setPosition(position);
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
			std::cout << "added " << weight << " to capacity" << std::endl;
			p_currentCapacity += weight;
		}
		else {
			std::cout << "max capacity" << std::endl;
		}
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
	Transform p_boatTransform = Transform(glm::vec3(0.0f, 0.0f, -200.0f));

	Mesh p_motorMesh = Mesh("data/models/motor.obj");
	Texture p_motorTexture = Texture("data/textures/motor.png");
	Transform p_motorTransform = Transform(glm::vec3(0.0f, 0.0f, 17.296f));

	Shader p_shader;

	glm::vec3 p_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f);

	const float p_minTurnRotation = 0.0f;
	const float p_maxTurnRotation = 1.0f;

	const float p_moveSpeed = 2.50f;
	const float p_turnSpeed = 0.01f;

	float p_currentCapacity = 0.0f;
	float p_maxCapacity = 25.0f;
};

#include "player.hpp"

void Player::draw(Camera camera, Light light, const float& elapsedTime) {
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

void Player::updateMovement(const float& time) {
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

void Player::moveForward() {
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

void Player::moveBack() {
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

void Player::turnLeft() {
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

void Player::turnRight() {
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

glm::vec3 Player::getCameraPosition() {
	glm::vec3 position = p_boatTransform.getPosition();
	position += 5.0f * p_up;
	position -= 7.0f * p_forward;
	return position;
}

glm::vec3 Player::getPosition() {
	return p_boatTransform.getPosition();
}

void Player::addToCapacity(float weight) {
	if (p_currentCapacity < p_maxCapacity) {
		p_currentCapacity += weight;
	}
	if (p_currentCapacity > p_maxCapacity) {
		p_currentCapacity = p_maxCapacity;
	}
}

float Player::getCurrentCapacity() {
	return p_currentCapacity;
}

float Player::getMaxCapacity() {
	return p_maxCapacity;
}

bool Player::isOverCapacity() {
	if (p_currentCapacity < p_maxCapacity) {
		return false;
	}
	else {
		return true;
	}
}

#include "player.hpp"

//void Player::turnLeft() {
	//glm::vec3 rotation = p_transform.getRotation();
	//rotation.y -= delta_turn;
	//p_transform.setRotation(rotation);
//}

//void Player::turnRight() {
	//glm::vec3 rotation = p_transform.getRotation();
	//rotation.y += delta_turn;
	//p_transform.setRotation(rotation);
//}

void Player::moveForward() {
	//glm::vec3 position = p_transform.getPosition();
	//position += p_forward;
	//p_transform.setPosition(position);
	std::cout << "forward!" << std::endl;
}

void Player::moveBack() {
	//glm::vec3 position = p_transform.getPosition();
	//position -= p_forward;
	//p_transform.setPosition(position);
	std::cout << "back!" << std::endl;
}

void Player::render() {
	p_texture.bind(0);
	p_mesh.render();
}

void Player::updateCamera() {
	glm::vec3 position = p_transform.getPosition();
	position.z -= 50.0f;
	p_camera = Camera(position, 70.0f, (float)(1280 / 720), 0.1f, 1000.0f);
}

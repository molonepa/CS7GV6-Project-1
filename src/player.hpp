#pragma once

#include "utils/camera.hpp"
#include "utils/transform.hpp"
#include "mesh.hpp"
#include "texture.hpp"

#include <string>
#include <iostream>

class Player {
public:
	Player(const glm::vec3& startPosition, const std::string& meshPath, const std::string& texturePath) {
		this->p_mesh = Mesh(meshPath);
		this->p_texture = Texture(texturePath);
		this->p_transform = Transform(startPosition);
		glm::vec3 cameraPosition = startPosition;
		cameraPosition.z = -50.0f;
		this->p_camera = Camera(cameraPosition, 70.0f, (float)(1280 / 720), 0.1f, 1000.0f);
		this->p_forward = p_camera.getForward();
	}

	void updateCamera();
	void render();

	//void turnLeft();
	//void turnRight();

	void moveForward();
	void moveBack();

	inline glm::mat4 getModelMatrix() { return p_transform.getModelMatrix(); }
	inline glm::mat4 getViewProjectionMatrix() { return p_camera.getViewProjectionMatrix(); }

private:
	Mesh p_mesh;
	Texture p_texture;
	Camera p_camera;

	Transform p_transform;
	glm::vec3 p_velocity = glm::vec3(0.0f);

	glm::vec3 p_forward;
};

#pragma once

#define PI 3.1415926353

#include "opengl/mesh.hpp"
#include "opengl/texture.hpp"
#include "opengl/shader.hpp"
#include "utils/transform.hpp"
#include "utils/camera.hpp"
#include "utils/light.hpp"

#include <glm/gtx/rotate_vector.hpp>

class Player {
public:
	void draw(Camera camera, Light light, const float& elapsedTime);

	void updateMovement(const float& time);

	void moveForward();

	void moveBack();

	void turnLeft();

	void turnRight();

	glm::vec3 getCameraPosition();

	glm::vec3 getPosition();

	void addToCapacity(float weight);

	float getCurrentCapacity();

	float getMaxCapacity();

	bool isOverCapacity();

private:
	Mesh p_boatMesh = Mesh("assets/models/boat.obj");
	Texture p_boatTexture = Texture("assets/textures/boat.png");
	Transform p_boatTransform = Transform(glm::vec3(0.0f, 0.0f, -1250.0f));

	Mesh p_motorMesh = Mesh("assets/models/motor.obj");
	Texture p_motorTexture = Texture("assets/textures/motor.png");
	Transform p_motorTransform = Transform(glm::vec3(0.0f, 0.0f, 17.296f));

	Shader p_shader;

	glm::vec3 p_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f);

	const float p_minTurnRotation = 0.0f;
	const float p_maxTurnRotation = 1.0f;

	const float p_acceleration = 0.1f;
	float p_currentSpeed = 0.0f;
	const float p_maxForwardsSpeed = 3.50f;
	const float p_maxBackwardsSpeed = -2.0f;
	const float p_turnSpeed = 0.01f;
	bool p_isMoving = false;

	float p_currentCapacity = 0.0f;
	float p_maxCapacity = 25.0f;
};

#pragma once

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"
#include "utils/random_float.hpp"

class Bottle {
public:
	inline void draw(Camera camera, Light light) {
		if (!p_isCollected) {
			p_shader.bind();
			p_shader.updateUniform("viewProjectionMatrix", camera.getViewProjectionMatrix());
			p_shader.updateUniform("camera_position", camera.getPosition());
			p_shader.updateUniform("light_colour", light.getColour());
			p_shader.updateUniform("light_position", light.getPosition());
			p_shader.updateUniform("ambient_strength", light.getStrength());
			p_shader.updateUniform("specular_strength", 0.8f);
			p_shader.updateUniform("reflection_strength", 0.8f);
			p_shader.updateUniform("modelMatrix", p_transform.getModelMatrix());
			p_texture.bind(0);
			p_mesh.render();
		}
	}

	inline void update(const float& time) {
		glm::vec3 pos = p_transform.getPosition();
		pos.y = -20.f + 2 * sin(0.1 * time);
		p_transform.setPosition(pos);

		glm::vec3 rot = p_transform.getRotation();
		rot.y += 0.00001 * time;
		p_transform.setRotation(rot);
	}

	inline glm::vec3 getPosition() {
		return p_transform.getPosition();
	}

	inline float getWeight() {
		return p_weight;
	}

	inline void collect() {
		p_isCollected = true;
	}

	inline bool isCollected() {
		return p_isCollected;
	}

private:
	Mesh p_mesh = Mesh("data/models/rubbish/bottle.obj");
	Texture p_texture = Texture("data/textures/plastic_bottle.png");
	Transform p_transform = Transform(glm::vec3(random_float(-3000, 3000), -45.0f, random_float(-3000, 3000)), glm::vec3(0.0f), glm::vec3(10.0f));
	Shader p_shader;

	float p_weight = 2.5f;
	bool p_isCollected = false;
};

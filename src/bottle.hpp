#pragma once

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"
#include "utils/random_float.hpp"

class Bottle {
public:
	inline void draw(Camera camera, Light light) {
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
private:
	Mesh p_mesh = Mesh("data/models/rubbish/bottle.obj");
	Texture p_texture;
	Transform p_transform = Transform(glm::vec3(random_float(-1000, 1000), -45.0f, random_float(-1000, 1000)));
	Shader p_shader;
};

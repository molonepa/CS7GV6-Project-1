#pragma once

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"

class World {
public:
	inline void draw(Camera camera, Light light, const float& time) {
		// render sky
		// disable depth testing to draw skybox
		glDisable(GL_DEPTH_TEST);

		p_skyShader.bind();
		p_skyShader.updateUniform("modelMatrix", p_skyTransform.getModelMatrix());
		p_skyShader.updateUniform("viewProjectionMatrix", camera.getViewProjectionMatrix());

		p_skyTexture.bind(0);
		p_skyMesh.render();

		// re-enable depth testing
		glEnable(GL_DEPTH_TEST);

		// render terrain
		p_terrainShader.bind();
		p_terrainShader.updateUniform("modelMatrix", p_terrainTransform.getModelMatrix());
		p_terrainShader.updateUniform("viewProjectionMatrix", camera.getViewProjectionMatrix());
		p_terrainShader.updateUniform("camera_position", camera.getPosition());
		p_terrainShader.updateUniform("light_colour", light.getColour());
		p_terrainShader.updateUniform("light_position", light.getPosition());
		p_terrainShader.updateUniform("ambient_strength", light.getStrength());
		p_terrainShader.updateUniform("specular_strength", 0.3f);
		p_terrainShader.updateUniform("reflection_strength", 0.3f);

		p_terrainTexture.bind(0);
		p_terrainMesh.render();

		// render water
		p_waterShader.bind();
		p_waterShader.updateUniform("modelMatrix", p_waterTransform.getModelMatrix());
		p_waterShader.updateUniform("viewProjectionMatrix", camera.getViewProjectionMatrix());
		p_waterShader.updateUniform("camera_position", camera.getPosition());
		p_waterShader.updateUniform("light_colour", light.getColour());
		p_waterShader.updateUniform("light_position", light.getPosition());
		p_waterShader.updateUniform("ambient_strength", light.getStrength());
		p_waterShader.updateUniform("specular_strength", 0.7f);
		p_waterShader.updateUniform("reflection_strength", 0.7f);
		p_waterShader.updateUniform("time", time);

		p_waterTexture.bind(0);
		p_waterMesh.render();
	}
private:
	Mesh p_terrainMesh = Mesh("data/models/ground_plane.obj");
	Texture p_terrainTexture = Texture("data/textures/sand.png");
	Transform p_terrainTransform = Transform(glm::vec3(0.0f, -150.0f, 0.0f), glm::vec3(0.0f), glm::vec3(50.0f, 20.0f, 50.0f));
	Shader p_terrainShader;

	Mesh p_waterMesh = Mesh("data/models/water.obj");
	Texture p_waterTexture = Texture("data/textures/water_clean.png");
	Transform p_waterTransform = Transform(glm::vec3(0.0f, -55.0f, 0.0f), glm::vec3(0.0f), glm::vec3(10.0f, 1.0f, 10.0f));
	Shader p_waterShader = Shader("src/shaders/water");

	Mesh p_skyMesh = Mesh("data/models/skybox.obj");
	Texture p_skyTexture = Texture({ "data/textures/skybox/miramar_right.jpg", "data/textures/skybox/miramar_left.jpg", "data/textures/skybox/miramar_top.jpg", "data/textures/skybox/miramar_bottom.jpg", "data/textures/skybox/miramar_front.jpg", "data/textures/skybox/miramar_back.jpg" });
	Transform p_skyTransform = Transform(glm::vec3(0.0f, 50000.0f, 0.0f), glm::vec3(0.0f), glm::vec3(100000.0f, 100000.0f, 100000.0f));
	Shader p_skyShader = Shader("src/shaders/sky");
};

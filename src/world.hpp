#pragma once

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"

class World {
public:
	inline void draw(glm::mat4 viewProjectionMatrix) {
		// disable depth testing to draw skybox
		glDisable(GL_DEPTH_TEST);
		p_skyShader.bind();
		p_skyShader.updateUniform("modelMatrix", p_skyTransform.getModelMatrix());
		p_skyShader.updateUniform("viewProjectionMatrix", viewProjectionMatrix);
		p_skyTexture.bind(0);
		p_skyMesh.render();
		// re-enable depth testing
		glEnable(GL_DEPTH_TEST);

		p_terrainShader.bind();
		p_terrainShader.updateUniform("modelMatrix", p_terrainTransform.getModelMatrix());
		p_terrainShader.updateUniform("viewProjectionMatrix", viewProjectionMatrix);
		p_terrainTexture.bind(0);
		p_terrainMesh.render();

		p_waterShader.bind();
		p_waterShader.updateUniform("modelMatrix", p_waterTransform.getModelMatrix());
		p_waterShader.updateUniform("viewProjectionMatrix", viewProjectionMatrix);
		p_waterTexture.bind(0);
		p_waterMesh.render();
	}
private:
	Mesh p_terrainMesh = Mesh("data/models/ground_plane.obj");
	Texture p_terrainTexture = Texture("data/textures/sea_floor.png");
	Transform p_terrainTransform = Transform(glm::vec3(0.0f, -50.0f, 0.0f), glm::vec3(0.0f), glm::vec3(5.0f, 5.0f, 5.0f));
	Shader p_terrainShader;

	Mesh p_waterMesh = Mesh("data/models/sea_plane.obj");
	Texture p_waterTexture = Texture("data/textures/water_texture.png");
	Transform p_waterTransform = Transform(glm::vec3(0.0f, -55.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1000.0f, 1.0f, 1000.0f));
	Shader p_waterShader = Shader("src/shaders/water");

	Mesh p_skyMesh = Mesh("data/models/skybox.obj");
	Texture p_skyTexture = Texture({ "data/textures/skybox/cloudy_right.jpg", "data/textures/skybox/cloudy_left.jpg", "data/textures/skybox/cloudy_top.jpg", "data/textures/skybox/cloudy_bottom.jpg", "data/textures/skybox/cloudy_front.jpg", "data/textures/skybox/cloudy_back.jpg" });
	Transform p_skyTransform = Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1000.0f, 1000.0f, 1000.0f));
	Shader p_skyShader = Shader("src/shaders/sky");
};

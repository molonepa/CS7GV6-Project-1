#pragma once

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"

class World {
public:
	inline void draw(glm::mat4 viewProjectionMatrix) {
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
	Transform p_waterTransform = Transform(glm::vec3(0.0f, -55.0f, 0.0f), glm::vec3(0.0f), glm::vec3(5.0f, 5.0f, 5.0f));
	Shader p_waterShader = Shader("src/shaders/water");
};

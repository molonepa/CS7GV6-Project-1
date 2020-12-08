#include "world.hpp"

void World::draw(Camera camera, Light light, const float& time) {
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
	p_waterShader.updateUniform("specular_strength", 2.0f);
	p_waterShader.updateUniform("reflection_strength", 8.0f);
	p_waterShader.updateUniform("time", time);

	p_waterShader.updateUniform("diffuse_map", 0);
	p_waterShader.updateUniform("normal_map", 1);
	p_waterShader.updateUniform("specular_map", 2);
	p_waterDiffuseMap.bind(0);
	p_waterNormalMap.bind(1);
	p_waterSpecularMap.bind(2);

	p_waterMesh.render();
}

void World::changeSkyTexture() {
	p_skyTexture = Texture({ "assets/textures/skybox/Daylight Box_Right.png", "assets/textures/skybox/Daylight Box_Left.png", "assets/textures/skybox/Daylight Box_Top.png", "assets/textures/skybox/Daylight Box_Bottom.png", "assets/textures/skybox/Daylight Box_Front.png", "assets/textures/skybox/Daylight Box_Back.png" });
}

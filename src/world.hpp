#pragma once

#include "opengl/mesh.hpp"
#include "opengl/texture.hpp"
#include "opengl/shader.hpp"
#include "utils/camera.hpp"
#include "utils/light.hpp"
#include "utils/transform.hpp"

class World {
public:
	void draw(Camera camera, Light light, const float& time);

private:
	Mesh p_terrainMesh = Mesh("assets/models/ground_plane.obj");
	Texture p_terrainTexture = Texture("assets/textures/sand.png");
	Transform p_terrainTransform = Transform(glm::vec3(0.0f, -150.0f, 0.0f), glm::vec3(0.0f), glm::vec3(50.0f, 20.0f, 50.0f));
	Shader p_terrainShader;

	Mesh p_waterMesh = Mesh("assets/models/water.obj");
	//Texture p_waterDiffuseMap = Texture("assets/textures/water_clean.png");
	Texture p_waterDiffuseMap = Texture("assets/textures/water_blue.png");
	Texture p_waterNormalMap = Texture("assets/textures/water_normal_map.png");
	Texture p_waterSpecularMap = Texture("assets/textures/water_specular_map.png");
	Transform p_waterTransform = Transform(glm::vec3(0.0f, -55.0f, 0.0f), glm::vec3(0.0f), glm::vec3(10.0f, 1.0f, 10.0f));
	Shader p_waterShader = Shader("src/shaders/water");

	Mesh p_skyMesh = Mesh("assets/models/skybox.obj");
	Texture p_skyTexture = Texture({ "assets/textures/skybox/miramar_right.jpg", "assets/textures/skybox/miramar_left.jpg", "assets/textures/skybox/miramar_top.jpg", "assets/textures/skybox/miramar_bottom.jpg", "assets/textures/skybox/miramar_front.jpg", "assets/textures/skybox/miramar_back.jpg" });
	Transform p_skyTransform = Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(100000.0f, 100000.0f, 100000.0f));
	Shader p_skyShader = Shader("src/shaders/sky");
};

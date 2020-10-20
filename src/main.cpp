#include "window.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "utils/vertex.hpp"
#include "utils/transform.hpp"
#include "utils/camera.hpp"

#include <iostream>

int main() {
	Window window(1280, 720, "Application");
	Shader defaultShader = Shader();

	Mesh boatMesh = Mesh("data/models/boat.obj");
	Texture boatTexture = Texture("data/textures/Fishing boat 1.png");

	Transform t;
	Camera c = Camera(glm::vec3(0.0f, 0.0f, 50.0f), 70.0f, (float)(1280 / 720), 0.1f, 1000.0f);

	float count = 0.0f;
	while (window.isOpen()) {
		window.clear(0.5f, 0.5f, 0.5f, 1.0f);

		glm::vec3 r = t.getRotation();
		r.x = count;
		r.y = count;
		r.z = count;
		t.setRotation(r);

		defaultShader.bind();
		defaultShader.updateUniform("modelMatrix", t.getModelMatrix());
		defaultShader.updateUniform("viewProjectionMatrix", c.getViewProjectionMatrix());
		boatTexture.bind(0);
		boatMesh.render();

		window.update();
		count += 0.0005f;
	}
	return 0;
}

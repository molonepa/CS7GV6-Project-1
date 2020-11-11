#include "utils/window_manager.hpp"
#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/vertex.hpp"
#include "utils/transform.hpp"
#include "utils/camera.hpp"
#include "utils/event_handler.hpp"
//#include "player.hpp"
#include "object_3d.hpp"

int main() {
	WindowManager window(1600, 900, "Application");
	Shader defaultShader = Shader();

	EventHandler input;
	Camera c(glm::vec3(0.0f, 50.0f, 50.0f));

	input.addBinding(SDL_SCANCODE_W, std::bind(&Camera::moveForward, &c));
	input.addBinding(SDL_SCANCODE_S, std::bind(&Camera::moveBack, &c));
	input.addBinding(SDL_SCANCODE_A, std::bind(&Camera::moveLeft, &c));
	input.addBinding(SDL_SCANCODE_D, std::bind(&Camera::moveRight, &c));

	//Mesh worldMesh = Mesh("data/models/ground_plane.obj");
	//Texture worldTexture = Texture("data/textures/sea_floor.png");
	//Transform worldTransform;

	//Mesh playerMesh = Mesh("data/models/boat.obj");
	//Texture playerTexture = Texture("data/textures/sea_floor.png");
	//Texture playerTexture;
	//Transform playerTransform = Transform(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.25f));

	Object3D cube;

	while (window.isOpen()) {
		input.handle();

		window.clear(0.3f, 0.5f, 0.8f, 1.0f);

		//defaultShader.bind();
		//defaultShader.updateUniform("modelMatrix", worldTransform.getModelMatrix());
		//defaultShader.updateUniform("viewProjectionMatrix", c.getViewProjectionMatrix());
		//worldTexture.bind(0);
		//worldMesh.render();

		//defaultShader.bind();
		//defaultShader.updateUniform("modelMatrix", playerTransform.getModelMatrix());
		//defaultShader.updateUniform("viewProjectionMatrix", c.getViewProjectionMatrix());
		//playerTexture.bind(0);
		//playerMesh.render();

		cube.draw(c.getViewProjectionMatrix());

		window.update();
	}

	return 0;
}

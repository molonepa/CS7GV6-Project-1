#include "window_manager.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "utils/vertex.hpp"
#include "utils/transform.hpp"
#include "utils/camera.hpp"
#include "utils/event_handler.hpp"
#include "player.hpp"

int main() {
	WindowManager window(1280, 720, "Application");
	Shader defaultShader = Shader();

	EventHandler input;

	//input.addBinding(SDL_SCANCODE_W, std::bind(&Player::moveForward, &player));
	//input.addBinding(SDL_SCANCODE_S, std::bind(&Player::moveBack, &player));
	//addBinding(SDLK_a, std::bind(&Player::turnLeft, &player));
	//addBinding(SDLK_d, std::bind(&Player::turnRight, &player));

	Player player = Player(glm::vec3(0.0f), "data/models/boat.obj", "data/textures/test_texture.png");

	//Mesh mesh;
	//Texture texture;
	//Transform t;
	//Camera c(glm::vec3(0.0f, 0.0f, 50.0f));

	SDL_Event e;
	float count = 0.0f;
	while (window.isOpen()) {
		input.handle();

		window.clear(0.5f, 0.5f, 0.5f, 1.0f);

		defaultShader.bind();

		defaultShader.updateUniform("modelMatrix", player.getModelMatrix());
		defaultShader.updateUniform("viewProjectionMatrix", player.getViewProjectionMatrix());
		//player.updateCamera();
		player.render();

		//defaultShader.updateUniform("modelMatrix", t.getModelMatrix());
		//defaultShader.updateUniform("viewProjectionMatrix", c.getViewProjectionMatrix());
		//texture.bind(0);
		//mesh.render();

		window.update();
		count += 0.0005f;
	}

	return 0;
}

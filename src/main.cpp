#include "utils/window_manager.hpp"
#include "utils/camera.hpp"
#include "utils/event_handler.hpp"
#include "player.hpp"
#include "world.hpp"

int main() {
	WindowManager window(1600, 900, "Application");

	EventHandler input;
	//Camera c(glm::vec3(0.0f, 500.0f, 500.0f));
	Camera c(glm::vec3(0.0f, 400.0f, 400.0f));

	Player player;
	input.addBinding(SDL_SCANCODE_W, std::bind(&Player::moveForward, &player));
	input.addBinding(SDL_SCANCODE_S, std::bind(&Player::moveBack, &player));
	input.addBinding(SDL_SCANCODE_A, std::bind(&Player::turnLeft, &player));
	input.addBinding(SDL_SCANCODE_D, std::bind(&Player::turnRight, &player));

	World world;

	while (window.isOpen()) {
		input.handle();

		window.clear(0.3f, 0.5f, 0.8f, 1.0f);

		world.draw(c.getViewProjectionMatrix());
		player.draw(c.getViewProjectionMatrix());

		window.update();
	}

	return 0;
}

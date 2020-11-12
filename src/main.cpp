#include "utils/window_manager.hpp"
#include "utils/camera.hpp"
#include "utils/event_handler.hpp"
#include "player.hpp"
#include "world.hpp"

#include "utils/clock.hpp"

float countdown = 1000.0f; // 1000 = 10 seconds for some reason

int main() {
	WindowManager window(1600, 900, "Application");
	Clock clock;

	EventHandler input;

	Camera c(glm::vec3(0.0f, 60.0f, 0.0f));
	input.addBinding(SDL_SCANCODE_UP, std::bind(&Camera::lookUp, &c));
	input.addBinding(SDL_SCANCODE_DOWN, std::bind(&Camera::lookDown, &c));
	input.addBinding(SDL_SCANCODE_LEFT, std::bind(&Camera::lookLeft, &c));
	input.addBinding(SDL_SCANCODE_RIGHT, std::bind(&Camera::lookRight, &c));

	Player player;
	input.addBinding(SDL_SCANCODE_W, std::bind(&Player::moveForward, &player));
	input.addBinding(SDL_SCANCODE_S, std::bind(&Player::moveBack, &player));
	input.addBinding(SDL_SCANCODE_A, std::bind(&Player::turnLeft, &player));
	input.addBinding(SDL_SCANCODE_D, std::bind(&Player::turnRight, &player));

	World world;

	while (window.isOpen() && countdown > 0) {
		float dt = clock.getDeltaTime();
		//countdown = countdown - dt;

		input.handle();

		window.clear(0.3f, 0.5f, 0.8f, 1.0f);

		world.draw(c.getViewProjectionMatrix());
		player.draw(c.getViewProjectionMatrix());

		window.update();

		clock.tick();
	}

	return 0;
}

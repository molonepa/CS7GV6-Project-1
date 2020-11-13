#include "utils/window_manager.hpp"
#include "utils/camera.hpp"
#include "utils/event_handler.hpp"
#include "utils/light.hpp"
#include "player.hpp"
#include "world.hpp"

#include "utils/clock.hpp"

float countdown = 1000.0f; // 1000 = 10 seconds for some reason

int main() {
	WindowManager window(1600, 900, "Application");
	Clock clock;

	EventHandler input;

	Light light = Light(glm::vec3(500.0f), glm::vec3(0.78f, 0.88f, 1.0f), 0.6f);

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
	input.addBinding(SDL_SCANCODE_LEFT, std::bind(&Camera::lookLeft, &camera));
	input.addBinding(SDL_SCANCODE_RIGHT, std::bind(&Camera::lookRight, &camera));

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

		window.clear(0.25f, 0.6f, 1.0f, 1.0f);

		world.draw(camera, light);
		player.draw(camera, light);

		camera.update(player.getCameraPosition(), player.getForward());

		window.update();

		clock.tick();
	}

	return 0;
}

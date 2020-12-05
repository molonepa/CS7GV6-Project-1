#include "utils/window_manager.hpp"
#include "utils/camera.hpp"
#include "utils/event_handler.hpp"
#include "utils/clock.hpp"
#include "utils/light.hpp"
#include "player.hpp"
#include "world.hpp"
#include "rubbish.hpp"

int main() {
	WindowManager window(1600, 900, "Application");

	Clock clock;

	EventHandler input;

	Light light = Light(glm::vec3(500.0f), glm::vec3(0.78f, 0.88f, 1.0f), 0.5f);

	Camera camera;
	input.addMouseBinding(std::bind(&Camera::turn, &camera, std::placeholders::_1, std::placeholders::_2));
	input.addKeyBinding(SDL_SCANCODE_M, std::bind(&Camera::activateMapMode, &camera));

	Player player;
	input.addKeyBinding(SDL_SCANCODE_W, std::bind(&Player::moveForward, &player));
	input.addKeyBinding(SDL_SCANCODE_S, std::bind(&Player::moveBack, &player));
	input.addKeyBinding(SDL_SCANCODE_A, std::bind(&Player::turnLeft, &player));
	input.addKeyBinding(SDL_SCANCODE_D, std::bind(&Player::turnRight, &player));

	World world;

	Rubbish rubbish;

	while (window.isOpen() && clock.getElapsedTime() < 10000) {
		input.handleKeyboardInput();
		input.handleMouseInput();

		if (!player.isOverCapacity()) {
			float weightToAdd = rubbish.collect(player.getPosition());
			if (weightToAdd > 0) {
				player.addToCapacity(weightToAdd);
			}
		}

		window.clear(0.25f, 0.6f, 1.0f, 1.0f);

		world.draw(camera, light, clock.getElapsedTime());
		player.draw(camera, light);
		rubbish.draw(camera, light);

		camera.update(player.getCameraPosition());


		ImGui::Begin("Clock");
		ImGui::Text("Delta: %0.2f", clock.getDeltaTime());
		ImGui::Text("Elapsed: %0.2f", clock.getElapsedTime());
		ImGui::End();

		window.update();

		clock.tick();
	}

	return 0;
}

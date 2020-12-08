#include "utils/camera.hpp"
#include "utils/event_handler.hpp"
#include "utils/clock.hpp"
#include "utils/light.hpp"
#include "opengl/window_manager.hpp"
#include "player.hpp"
#include "world.hpp"
#include "rubbish.hpp"

const float TOTAL_TIME_ALLOWED = 6000.0f;

int main() {
	WindowManager window(1600, 900, "Application");

	Clock clock;

	EventHandler input;

	Light light = Light(glm::vec3(5000.0f), glm::vec3(0.78f, 0.88f, 1.0f), 0.5f);

	Camera camera;
	Camera endCamera = Camera(glm::vec3(0.0f, 500.0f, 0.0f));
	input.addMouseBinding(std::bind(&Camera::turn, &camera, std::placeholders::_1, std::placeholders::_2));
	input.addMouseBinding(std::bind(&Camera::turn, &endCamera, std::placeholders::_1, std::placeholders::_2));
	input.addKeyBinding(SDL_SCANCODE_M, std::bind(&Camera::activateMapMode, &camera));

	Player player;
	input.addKeyBinding(SDL_SCANCODE_W, std::bind(&Player::moveForward, &player));
	input.addKeyBinding(SDL_SCANCODE_S, std::bind(&Player::moveBack, &player));
	input.addKeyBinding(SDL_SCANCODE_A, std::bind(&Player::turnLeft, &player));
	input.addKeyBinding(SDL_SCANCODE_D, std::bind(&Player::turnRight, &player));
	int maxCapacity = (int)player.getMaxCapacity();
	float totalCollectedRubbish = 0.0f;

	World world;

	Rubbish rubbish;

	//main game loop
	while (window.isOpen() && clock.getElapsedTime() < TOTAL_TIME_ALLOWED) {
		// handle user input
		input.handleKeyboardInput();
		input.handleMouseInput();

		// update game logic
		if (!player.isOverCapacity()) {
			float weightToAdd = rubbish.collect(player.getPosition());
			if (weightToAdd > 0) {
				player.addToCapacity(weightToAdd);
			}
		}

		// render graphics
		window.clear(0.25f, 0.6f, 1.0f, 1.0f);
		world.draw(camera, light, clock.getElapsedTime());
		player.draw(camera, light, clock.getElapsedTime());
		rubbish.draw(camera, light, clock.getElapsedTime());

		// render UI
		ImGui::Begin("Information", NULL, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::PushItemWidth(500);
		ImGui::Text("\nGameplay:\n");
		ImGui::Text("Capacity: %0.1f/%d", player.getCurrentCapacity(), maxCapacity);
		//ImGui::Text("Delta time: %0.2f", clock.getDeltaTime());
		ImGui::Text("Time remaining: %ds", (int)(TOTAL_TIME_ALLOWED - clock.getElapsedTime()) / 100);
		ImGui::Text("\nControls:\nmouse - move camera\nW - move forwards\nS - move backwards\nA - turn left\nD - turn right\nM - enter map mode\nU - unload");
		ImGui::End();

		camera.update(player.getCameraPosition());
		window.update();

		// update clock
		clock.tick();
	}

	std:: string message;
	if (totalCollectedRubbish >= 100.0f) {
		world.changeSkyTexture();
		message = "Congratulations, you won!";
	}
	else {
		message = "Sorry, you lost!";
	}

	while (window.isOpen()) {
		input.handleMouseInput();

		// render graphics
		window.clear(0.25f, 0.6f, 1.0f, 1.0f);
		world.draw(endCamera, light, clock.getElapsedTime());

		// render UI
		ImGui::Begin("Game Over", NULL, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::PushItemWidth(500);
		ImGui::Text(message.c_str());
		ImGui::Text("You collected %0.1fkg of rubbish in total", totalCollectedRubbish);
		ImGui::End();

		window.update();

		// update clock
		clock.tick();
	}

	return 0;
}

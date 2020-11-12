#pragma once

#include <SDL2/SDL.h>

const int TARGET_FRAMERATE = 60;
const float TARGET_DELTA_TIME = 1.5f;

class Clock {
public:
	void tick() {
		p_deltaTime = (SDL_GetTicks() - p_lastTime) * (TARGET_FRAMERATE / 1000.0f);

		if (p_deltaTime > TARGET_DELTA_TIME) {
			p_deltaTime = TARGET_DELTA_TIME;
		}

		p_lastTime = SDL_GetTicks();
	}

	inline float getDeltaTime() { return p_deltaTime; }

private:
	float p_deltaTime;
	float p_lastTime;
};

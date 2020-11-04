#pragma once

#include <SDL2/SDL.h>

#include <functional>
#include <map>
#include <vector>

class EventHandler {
public:
	using Callback = std::function<void()>;

	inline void addBinding(int key, const Callback& callback) {
		p_callbacks[key].push_back(callback);
		p_keys.push_back(key);
	}

	inline void onKeyPress(int key) {
		for (Callback& callback : p_callbacks[key]) {
	    	callback();
		}
	}

	inline void handle() {
		const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
		for (auto key : p_keys) {
			if (keyboardState[key]) {
				onKeyPress(key);
			}
		}
	}

private:
	std::map<int, std::vector<Callback>> p_callbacks;
	std::vector<int> p_keys;
};

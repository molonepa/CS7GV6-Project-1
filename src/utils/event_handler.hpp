#pragma once

#include <SDL2/SDL.h>

#include <functional>
#include <map>
#include <vector>

class EventHandler {
public:
	using Callback = std::function<void()>;
	using MouseCallback = std::function<void(int, int)>;

	inline void addKeyBinding(int key, const Callback& callback) {
		p_keyCallbacks[key].push_back(callback);
		p_usedKeys.push_back(key);
	}

	inline void addMouseBinding(const MouseCallback& callback) {
		p_mouseMoveCallbacks.push_back(callback);
	}

	inline void onKeyPress(int key) {
		for (Callback& callback : p_keyCallbacks[key]) {
	    	callback();
		}
	}

	inline void onMouseMove(int x, int y) {
		for (MouseCallback& callback : p_mouseMoveCallbacks) {
	    	callback(x, y);
		}
	}

	inline void handleKeyboardInput() {
		const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
		for (auto key : p_usedKeys) {
			if (keyboardState[key]) {
				onKeyPress(key);
			}
		}
	}

	inline void handleMouseInput() {
		int dx, dy;
		SDL_GetRelativeMouseState(&dx, &dy);
		onMouseMove(dx, dy);
	}

private:
	std::map<int, std::vector<Callback>> p_keyCallbacks;
	std::vector<int> p_usedKeys;

	std::vector<MouseCallback> p_mouseMoveCallbacks;
};

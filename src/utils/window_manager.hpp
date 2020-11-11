#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>
#include <iostream>

class WindowManager {
public:
	WindowManager(int width, int height, const std::string& title);
	virtual ~WindowManager();

	void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	void update();

	inline bool isOpen() { return p_isOpen; }

private:
	SDL_Window* p_window;
	SDL_GLContext p_glContext;
	bool p_isOpen;
};

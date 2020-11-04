#include "window_manager.hpp"

WindowManager::WindowManager(int width, int height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING);

	// assign 8 bits each to R, G, B, A channels
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// 32 bits total
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	// 16 bit depth buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	// double buffer - one for drawing, one for displaying
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// create centered window that uses OpenGL
	p_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	// create OpenGL context for window
	p_glContext = SDL_GL_CreateContext(p_window);

	// initialise GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("ERROR: Failed to initialise GLEW");
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	p_isOpen = true;
}

WindowManager::~WindowManager() {
	// delete OpenGL context
	SDL_GL_DeleteContext(p_glContext);

	// delete window
	SDL_DestroyWindow(p_window);
	SDL_Quit();
}

void WindowManager::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::update() {
	// swap displaying and drawing buffers
	SDL_GL_SwapWindow(p_window);

	// update until quit
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			p_isOpen = false;
		}
	}
}

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

	// hide mouse cursor
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// initialise GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("ERROR: Failed to initialise GLEW");
	}

	//glEnable(GL_FRAMEBUFFER_SRGB);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(p_window, p_glContext);
	ImGui_ImplOpenGL3_Init();

	p_isOpen = true;
}

WindowManager::~WindowManager() {
	// cleanup imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	// delete OpenGL context
	SDL_GL_DeleteContext(p_glContext);

	// delete window
	SDL_DestroyWindow(p_window);
	SDL_Quit();
}

void WindowManager::clear(float r, float g, float b, float a) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(p_window);
	ImGui::NewFrame();

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::update() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// update until quit
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT) {
			p_isOpen = false;
		}
	}

	// swap displaying and drawing buffers
	SDL_GL_SwapWindow(p_window);
}

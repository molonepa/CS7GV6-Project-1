OBJS = src/opengl/window_manager.cpp src/opengl/shader.cpp src/opengl/mesh.cpp src/opengl/texture.cpp src/utils/obj_loader.cpp
IMGUI = external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_widgets.cpp external/imgui/backends/imgui_impl_sdl.cpp external/imgui/backends/imgui_impl_opengl3.cpp
LDFLAGS = -lSDL2 -I/usr/include/SDL2/ -lGL -lGLEW -lfreetype -I/usr/include/freetype2 -Iexternal/imgui/

# Main

Main: src/main.cpp $(OBJS)
	g++ -o build/Main src/main.cpp $(OBJS) $(IMGUI) $(LDFLAGS)

run: Main
	./build/Main

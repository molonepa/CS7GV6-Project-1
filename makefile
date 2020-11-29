OBJS = src/utils/window_manager.cpp src/utils/shader.cpp src/utils/mesh.cpp src/utils/texture.cpp src/utils/obj_loader.cpp
IMGUI = external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_widgets.cpp external/imgui/backends/imgui_impl_sdl.cpp external/imgui/backends/imgui_impl_opengl3.cpp
LDFLAGS = -lSDL2 -I/usr/include/SDL2/ -lGL -lGLEW -lfreetype -I/usr/include/freetype2 -Iexternal/imgui/

# Tests

WindowTest: tests/windowtest.cpp $(OBJS)
	g++ -o build/WindowTest tests/windowtest.cpp $(OBJS) $(LDFLAGS)

VertexTest: tests/vertextest.cpp $(OBJS)
	g++ -o build/VertexTest tests/vertextest.cpp $(OBJS) $(LDFLAGS)

ShaderTest: tests/shader_test.cpp $(OBJS)
	g++ -o build/ShaderTest tests/shader_test.cpp $(OBJS) $(LDFLAGS)

MeshTest: tests/mesh_test.cpp $(OBJS)
	g++ -o build/MeshTest tests/mesh_test.cpp $(OBJS) $(LDFLAGS)

TESTS = WindowTest VertexTest ShaderTest MeshTest

tests: $(TESTS)
	./build/WindowTest
	./build/VertexTest
	./build/ShaderTest
	./build/MeshTest

# Main

Main: src/main.cpp $(OBJS)
	g++ -o build/Main src/main.cpp $(OBJS) $(IMGUI) $(LDFLAGS)

run: Main
	./build/Main

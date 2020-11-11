OBJS = src/utils/window_manager.cpp src/utils/shader.cpp src/utils/mesh.cpp src/utils/texture.cpp src/utils/obj_loader.cpp
LDFLAGS = -lSDL2 -lGL -lGLEW

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
	g++ -o build/Main src/main.cpp $(OBJS) $(LDFLAGS)

run: Main
	./build/Main

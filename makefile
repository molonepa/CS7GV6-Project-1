OBJS = src/window.cpp src/shader.cpp src/mesh.cpp src/texture.cpp src/utils/obj_loader.cpp
LDFLAGS = -lglfw -lGL -lGLEW

# Tests

WindowTest: tests/windowtest.cpp $(OBJS)
	g++ -o build/WindowTest tests/windowtest.cpp $(OBJS) $(LDFLAGS)

VertexTest: tests/vertextest.cpp $(OBJS)
	g++ -o build/VertexTest tests/vertextest.cpp $(OBJS) $(LDFLAGS)

VerticesTest: tests/vector_of_vertices_test.cpp $(OBJS)
	g++ -o build/VerticesTest tests/vector_of_vertices_test.cpp $(OBJS) $(LDFLAGS)

MeshTest: tests/mesh_test.cpp $(OBJS)
	g++ -o build/MeshTest tests/mesh_test.cpp $(OBJS) $(LDFLAGS)

ShaderTest: tests/shader_test.cpp $(OBJS)
	g++ -o build/ShaderTest tests/shader_test.cpp $(OBJS) $(LDFLAGS)

TextureTest: tests/texture_test.cpp $(OBJS)
	g++ -o build/TextureTest tests/texture_test.cpp $(OBJS) $(LDFLAGS)

OBJTextureTest: tests/obj_texture_test.cpp $(OBJS)
	g++ -o build/OBJTextureTest tests/obj_texture_test.cpp $(OBJS) $(LDFLAGS)

TESTS = WindowTest VertexTest VerticesTest ShaderTest MeshTest TextureTest OBJTextureTest

tests: $(TESTS)
	./build/WindowTest
	./build/VertexTest
	./build/VerticesTest
	./build/ShaderTest
	./build/MeshTest
	./build/TextureTest
	./build/OBJTextureTest

# Main

Main: src/main.cpp $(OBJS)
	g++ -o build/Main src/main.cpp $(OBJS) $(LDFLAGS)

run: Main
	./build/Main

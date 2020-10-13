OBJS = src/window.cpp src/shader.cpp
LDFLAGS = -lglfw -lGL -lGLEW

# Tests

WindowTest: tests/windowtest.cpp $(OBJS)
	g++ -o build/WindowTest tests/windowtest.cpp $(OBJS) $(LDFLAGS)

VertexTest: tests/vertextest.cpp $(OBJS)
	g++ -o build/VertexTest tests/vertextest.cpp $(OBJS) $(LDFLAGS)

VerticesTest: tests/vector_of_vertices_test.cpp $(OBJS)
	g++ -o build/VerticesTest tests/vector_of_vertices_test.cpp $(OBJS) $(LDFLAGS)

ShaderTest: tests/shader_test.cpp $(OBJS)
	g++ -o build/ShaderTest tests/shader_test.cpp $(OBJS) $(LDFLAGS)

TESTS = WindowTest VertexTest VerticesTest ShaderTest

tests: $(TESTS)
	./build/WindowTest
	./build/VertexTest
	./build/VerticesTest
	./build/ShaderTest

# Main

Main: src/main.cpp $(OBJS)
	g++ -o build/Main src/main.cpp $(OBJS) $(LDFLAGS)

run: Main
	./build/Main

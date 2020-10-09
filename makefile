OBJS = src/window.cpp
LDFLAGS = -lglfw -lGL -lGLEW

# Tests

WindowTest: tests/windowtest.cpp $(OBJS)
	g++ -o build/WindowTest tests/windowtest.cpp $(OBJS) $(LDFLAGS)

VertexTest: tests/vertextest.cpp $(OBJS)
	g++ -o build/VertexTest tests/vertextest.cpp $(OBJS) $(LDFLAGS)

VerticesTest: tests/vector_of_vertices_test.cpp $(OBJS)
	g++ -o build/VerticesTest tests/vector_of_vertices_test.cpp $(OBJS) $(LDFLAGS)

TESTS = WindowTest VertexTest VerticesTest

tests: $(TESTS)
	./build/WindowTest
	./build/VertexTest
	./build/VerticesTest

# Main

Main: src/main.cpp $(OBJS)
	g++ -o build/Main src/main.cpp $(OBJS) $(LDFLAGS)

run: Main
	./build/Main

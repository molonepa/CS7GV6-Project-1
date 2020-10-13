#version 400

in vec3 vert_position;
in vec4 vert_colour;

out vec4 colour;

void main() {
	gl_Position = vec4(vert_position, 1.0);
	colour = vert_colour;
}

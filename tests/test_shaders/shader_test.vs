#version 400

in vec4 vert_colour;

uniform bool u_bool;
uniform int u_int;
uniform float u_float;
uniform float u_double;
uniform vec2 u_vec2;
uniform vec3 u_vec3;
uniform vec4 u_vec4;
uniform mat3 u_mat3;
uniform mat4 u_mat4;

out vec4 colour;

void main() {
	colour = vert_colour;
}

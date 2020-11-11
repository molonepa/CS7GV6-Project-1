#version 400

in vec3 vert_position;
in vec2 vert_uv;
in vec3 vert_normal;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

out vec2 frag_uv;

void main() {
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(vert_position, 1.0);
	frag_uv = vert_uv;
}

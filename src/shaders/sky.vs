#version 400

in vec3 vert_position;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

out vec3 frag_uv;

void main() {
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(vert_position, 1.0);
	frag_uv = vert_position;
}

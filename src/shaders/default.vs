#version 400

in vec3 vert_position;
in vec2 vert_uv;
in vec3 vert_normal;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

out vec3 frag_position;
out vec2 frag_uv;
out vec3 frag_normal;

void main() {
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(vert_position, 1.0);

	frag_position = (modelMatrix * vec4(vert_position, 1.0f)).xyz;
	frag_uv = vert_uv;
	frag_normal = vert_normal;
}

#version 400

in vec3 vert_position;
in vec2 vert_uv;
in vec3 vert_normal;

out vec2 frag_uv;

void main() {
	gl_Position = vec4(vert_position, 1.0);
	frag_uv = vert_uv;
}

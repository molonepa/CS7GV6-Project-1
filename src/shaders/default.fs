#version 400

in vec2 frag_uv;

uniform sampler2D diffuse;

out vec4 frag_colour;

void main() {
	frag_colour = texture2D(diffuse, frag_uv);
}

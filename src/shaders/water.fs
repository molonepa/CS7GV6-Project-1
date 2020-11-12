#version 400

in vec2 frag_uv;

uniform sampler2D diffuse_dirty;
uniform sampler2D diffuse_clean;

out vec4 frag_colour;

void main() {
	frag_colour = texture2D(diffuse_dirty, frag_uv);
	//frag_colour = texture2D(diffuse_clean, frag_uv);
	frag_colour.a = 0.75;
}

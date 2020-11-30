#version 400

#define PI 3.1415926353

in vec3 vert_position;
in vec2 vert_uv;
in vec3 vert_normal;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;
uniform float time;

out vec2 frag_uv;

float displaceSurface(float x, float z) {
	// low frequency high amplitude in x dir
	float y = 10 * (sin(2 * PI * 0.0002 * time + 1.7) + sin(2 * PI * 0.0002 * x + 1.7));
	// med frequency med amplitude in x dir
	y += 5 * (sin(2 * PI * 0.001 * time + 3.1) + sin(2 * PI * 0.001 * x + 3.1));
	// high frequency low amplitude in x dir
	y += 3 * (sin(2 * PI * 0.005 * time + 2.5) + sin(2 * PI * 0.005 * x + 2.5));

	// low frequency high amplitude in z dir
	y += 10 * (sin(2 * PI * 0.0002 * time + 2.5) + sin(2 * PI * 0.0002 * x + 2.5));
	// med frequency med amplitude in z dir
	y += 5 * (sin(2 * PI * 0.001 * time + 1.7) + sin(2 * PI * 0.001 * x + 1.7));
	// high frequency low amplitude in z dir
	y += 3 * (sin(2 * PI * 0.005 * time + 3.1) + sin(2 * PI * 0.005 * x + 3.1));

	return y;
}

void main() {
	vec3 vp = vert_position;
	vp.y = displaceSurface(vp.x, vp.z);
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(vp, 1.0);
	frag_uv = vert_uv;
}

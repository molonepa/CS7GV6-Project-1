#version 400

#define PI 3.1415926353

in vec3 vert_position;
in vec2 vert_uv;
in vec3 vert_normal;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;
uniform float time;

out vec3 frag_position;
out vec2 frag_uv;

// displace using wave equation
// y(x, time) = A * sin(2*Pi/wavelength * (x-f*time) + phase)
// in both x and z directions
float displaceSurface(float x, float z) {
	float y = 10 * sin((2 * PI / 50) * (x - 0.01 * time));
	y += 5 * sin((2 * PI / 20) * (x - 0.05 * time));
	y += sin((2 * PI / 5) * (x - 0.1 * time));

	y += 10 * sin((2 * PI / 50) * (z - 0.01 * time) + 0.5);
	y += 5 * sin((2 * PI / 20) * (z - 0.05 * time) + 0.5);
	y += sin((2 * PI / 5) * (z - 0.1 * time) + 0.5);

	return y;
}

void main() {
	vec3 vp = vert_position;
	vp.y = displaceSurface(vp.x, vp.z);
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(vp, 1.0);

	frag_position = (modelMatrix * vec4(vp, 1.0f)).xyz;
	frag_uv = vert_uv;
}

#version 400

#define PI 3.1415926353

in vec3 frag_position;
in vec2 frag_uv;
in vec3 frag_normal;

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;
uniform sampler2D specular_map;

uniform vec3 light_colour;
uniform vec3 light_position;
uniform vec3 camera_position;

uniform float ambient_strength;
uniform float specular_strength;
uniform float reflection_strength;

uniform float time;

out vec4 frag_colour;

float distortTextureLookup(float a) {
	//float b = 10 * sin((2 * PI / 50) * (a - 0.01 * time));
	float b = 5 * sin((2 * PI / 20) * (a - 0.05 * time));
	b += sin((2 * PI / 5) * (a - 0.05 * time) + 0.25);
	return 0.01 * b;
}

void main() {
	vec2 uv = 50 * frag_uv;
	//uv.x += time * 0.001;
	//uv.y += time * 0.001;
	uv.x += distortTextureLookup(uv.y);
	uv.y += distortTextureLookup(uv.x);

	vec3 normal = frag_normal + texture2D(normal_map, uv).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 result = vec3(0.0);

	vec3 light_direction = normalize(light_position - frag_position);
	vec3 view_direction = normalize(camera_position - frag_position);
	vec3 halfway_direction = normalize(light_direction + view_direction);

	vec3 ambient_component = ambient_strength * vec3(texture2D(diffuse_map, uv));
	vec3 diffuse_component = max(dot(normalize(normal), light_direction), 0.0) * vec3(texture2D(diffuse_map, uv));
	vec3 specular_component = specular_strength * pow(max(dot(normal, halfway_direction), 0.0), reflection_strength) * vec3(texture2D(diffuse_map, uv));

	result = light_colour * (ambient_component + diffuse_component + specular_component);

	frag_colour = vec4(result, 0.8);
}

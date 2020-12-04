#version 400

in vec3 frag_position;
in vec2 frag_uv;

uniform sampler2D diffuse;
uniform sampler2D bump;

uniform vec3 light_colour;
uniform vec3 light_position;
uniform vec3 camera_position;

uniform float ambient_strength;
uniform float specular_strength;
uniform float reflection_strength;

uniform float time;

out vec4 frag_colour;

void main() {
	vec2 uv = 100 * frag_uv;
	uv.x += time * 0.005;
	uv.y += time * 0.005;

	vec3 normal = texture2D(bump, uv).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 result = vec3(0.0);

	vec3 light_direction = normalize(light_position - frag_position);
	vec3 view_direction = normalize(camera_position - frag_position);
	vec3 halfway_direction = normalize(light_direction + view_direction);

	vec3 ambient_component = ambient_strength * light_colour;
	vec3 diffuse_component = max(dot(normalize(normal), light_direction), 0.0) * light_colour;
	vec3 specular_component = specular_strength * pow(max(dot(normal, halfway_direction), 0.0), reflection_strength) * light_colour;

	result = ambient_component + diffuse_component + specular_component;

	frag_colour = vec4(result, 0.8) * texture2D(diffuse, uv);
}

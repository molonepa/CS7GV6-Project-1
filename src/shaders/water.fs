#version 400

in vec3 frag_position;
in vec2 frag_uv;
in vec3 frag_normal;

uniform sampler2D diffuse;

uniform vec3 light_colour;
uniform vec3 light_position;
uniform vec3 camera_position;

uniform float ambient_strength;
uniform float specular_strength;
uniform float reflection_strength;

uniform float time;

out vec4 frag_colour;

void main() {
	vec3 result = vec3(0.0);

	vec3 light_direction = normalize(light_position - frag_position);
	vec3 view_direction = normalize(camera_position - frag_position);
	vec3 reflect_direction = reflect(-light_direction, normalize(frag_normal));

	vec3 ambient_component = ambient_strength * light_colour;
	vec3 diffuse_component = max(dot(normalize(frag_normal), light_direction), 0.0) * light_colour;
	vec3 specular_component = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), reflection_strength) * light_colour;

	result = ambient_component + diffuse_component + specular_component;

	vec2 uv = 100 * frag_uv;
	uv.x += time * 0.001;
	//frag_colour = vec4(result, 1.0) * texture2D(diffuse, uv);
	frag_colour = vec4(result, 0.8) * texture2D(diffuse, uv);
}

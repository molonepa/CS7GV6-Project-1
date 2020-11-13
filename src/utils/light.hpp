#pragma once

#include <glm/glm.hpp>

class Light {
public:
	Light(glm::vec3 position = glm::vec3(0.0f), glm::vec3 colour = glm::vec3(1.0f), float strength = 1.0f) {
		p_position = position;
		p_colour = colour;
		p_strength = strength;
	}

	inline glm::vec3 getPosition() { return p_position; }
	inline glm::vec3 getColour() { return p_colour; }
	inline float getStrength() { return p_strength; }

	inline void setPosition(glm::vec3 p) { p_position = p; }

private:
	glm::vec3 p_position;
	glm::vec3 p_colour;
	float p_strength;
};

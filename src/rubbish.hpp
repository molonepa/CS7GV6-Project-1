#pragma once

#include "utils/distance.hpp"
#include "utils/camera.hpp"
#include "utils/light.hpp"
#include "bottle.hpp"
#include "can.hpp"

class Rubbish {
public:
	void draw(Camera camera, Light light, const float& elapsedTime);

	float collect(glm::vec3 playerPos);

private:
	Bottle bottles[100];
	Can cans[100];
};

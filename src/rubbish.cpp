#include "rubbish.hpp"

void Rubbish::draw(Camera camera, Light light, const float& elapsedTime) {
	for (int i = 0; i < 100; i++) {
		bottles[i].update(elapsedTime);
		bottles[i].draw(camera, light);
		cans[i].update(elapsedTime);
		cans[i].draw(camera, light);
	}
}

float Rubbish::collect(glm::vec3 playerPos) {
	float totalCollectedWeight = 0.0f;
	for (int i = 0; i < 100; i++) {
		// bottle
		glm::vec3 rubbishPos = bottles[i].getPosition();
		float d = distance(playerPos.x, rubbishPos.x, playerPos.z, rubbishPos.z);
		if (d < 10.0f && !bottles[i].isCollected()) {
			bottles[i].collect();
			totalCollectedWeight += bottles[i].getWeight();
		}
		// can
		rubbishPos = cans[i].getPosition();
		d = distance(playerPos.x, rubbishPos.x, playerPos.z, rubbishPos.z);
		if (d < 10.0f && !cans[i].isCollected()) {
			cans[i].collect();
			totalCollectedWeight += cans[i].getWeight();
		}
	}
	return totalCollectedWeight;
}

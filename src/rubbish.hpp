#pragma once

#include "utils/distance.hpp"
#include "bottle.hpp"
#include "can.hpp"
#include "cup.hpp"

class Rubbish {
public:
	inline void draw(Camera camera, Light light) {
		for (int i = 0; i < 50; i++) {
			bottles[i].draw(camera, light);
			cans[i].draw(camera, light);
			cups[i].draw(camera, light);
		}
	}

	inline float collect(glm::vec3 playerPos) {
		float totalCollectedWeight = 0.0f;
		for (int i = 0; i < 50; i++) {
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
			// cup
			rubbishPos = cups[i].getPosition();
			d = distance(playerPos.x, rubbishPos.x, playerPos.z, rubbishPos.z);
			if (d < 10.0f && !cups[i].isCollected()) {
				cups[i].collect();
				totalCollectedWeight += cups[i].getWeight();
			}
		}
		return totalCollectedWeight;
	}

private:
	Bottle bottles[50];
	Can cans[50];
	Cup cups[50];
};

#pragma once

#include "bottle.hpp"
#include "can.hpp"
#include "cup.hpp"

class Rubbish {
public:
	inline void draw(Camera camera, Light light) {
		bottle1.draw(camera, light);
		bottle2.draw(camera, light);
		bottle3.draw(camera, light);
		bottle4.draw(camera, light);
		bottle5.draw(camera, light);
		bottle6.draw(camera, light);
		bottle7.draw(camera, light);

		can1.draw(camera, light);
		can2.draw(camera, light);
		can3.draw(camera, light);
		can4.draw(camera, light);
		can5.draw(camera, light);
		can6.draw(camera, light);
		can7.draw(camera, light);
		can8.draw(camera, light);
		can9.draw(camera, light);
		can10.draw(camera, light);

		cup1.draw(camera, light);
		cup2.draw(camera, light);
		cup3.draw(camera, light);
		cup4.draw(camera, light);
	}
private:
	Bottle bottle1;
	Bottle bottle2;
	Bottle bottle3;
	Bottle bottle4;
	Bottle bottle5;
	Bottle bottle6;
	Bottle bottle7;
	Can can1;
	Can can2;
	Can can3;
	Can can4;
	Can can5;
	Can can6;
	Can can7;
	Can can8;
	Can can9;
	Can can10;
	Cup cup1;
	Cup cup2;
	Cup cup3;
	Cup cup4;
};

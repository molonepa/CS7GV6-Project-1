#pragma once

inline float random_float(float min, float max) {
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}

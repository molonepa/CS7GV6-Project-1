#include <math.h>

inline float distance(float x1, float x2, float y1, float y2) {
	float x = pow((x1 - x2), 2);
	float y = pow((y1 - y2), 2);
	return sqrt(x + y);
}

#ifndef _RT_MATH_H_
#define _RT_MATH_H_
#define PI 3.1415
#include <random>
#include "Vector2.h"
#include "Vector3.h"

inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

inline double radians(double degrees) {
	return degrees * PI / 180.0;
}
#endif
#include "Ray.h"

Ray::Ray() {

}

Ray::Ray(const Point& p_origin, const Vec3& p_direction) : origin(p_origin), direction(p_direction) {

}

Ray::~Ray() {

}

Point Ray::GetOrigin() const {
	return origin;
}
Vec3 Ray::GetDirection() const {
	return direction;
}

Point Ray::At(double delta_time) const {
	return origin + (direction * delta_time);
}
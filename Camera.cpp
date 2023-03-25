#include "Camera.h"

Camera::Camera(double p_fov, double p_aspect_ratio, double near, double far) {
	position = Vec3(0.0, 0.0, 0.0);
	w = tan(radians(p_fov) / 2);
	view_x = Vec3(2.0 * w, 0.0, 0.0);
	view_y = Vec3(0.0, 2.0 * w / p_aspect_ratio, 0.0);
	std::cerr << "Aspect Ratio: " << p_aspect_ratio << "\n" << std::flush;
	std::cerr << "Viewport <x: " << view_x.length() << ", y: " << view_y.length() << ">\n" << std::flush;
	lower_left_corner = position - view_x / 2.0 - view_y / 2.0 - Vec3(0, 0, near);
}

Camera::Camera(double p_fov, double p_aspect_ratio, double near, double far, const Point &p_position, const Point &p_target, const Vec3& up) : position(p_position) {
	w = tan(radians(p_fov) / 2);
	Vec3 z = (p_target - p_position).normalize();
	std::cerr << "Z-VEC <x: " << z.x() << ", y: " << z.y() << ", z: " << z.z() << ">\n" << std::flush;
	Vec3 x = cross(z, up).normalize();
	std::cerr << "X-VEC <x: " << x.x() << ", y: " << x.y() << ", z: " << x.z() << ">\n" << std::flush;
	Vec3 y = cross(x, z).normalize();
	std::cerr << "Y-VEC <x: " << y.x() << ", y: " << y.y() << ", z: " << y.z() << ">\n" << std::flush;
	view_x = 2.0 * w * x;
	view_y = 2.0 * w * y / p_aspect_ratio;
	std::cerr << "Aspect Ratio: " << p_aspect_ratio << "\n" << std::flush;
	std::cerr << "Viewport <x: " << view_x.length() << ", y: " << view_y.length() << ">\n" << std::flush;
	lower_left_corner = position - view_x / 2.0 - view_y / 2.0 + near*z;
}

Camera::~Camera() {

}

Ray Camera::CastRay(double x, double y) const {
	return Ray(position, lower_left_corner + x * view_x + y * view_y - position);
}
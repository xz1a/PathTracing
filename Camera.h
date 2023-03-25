#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Math.h"
#include "Ray.h"
#include <iostream>

class Camera {
public:
	Camera(double p_fov, double p_aspect_ratio, double near, double far);
	Camera(double p_fov, double p_aspect_ratio, double near, double far, const Point &p_position, const Point &p_target, const Vec3 &up);
	~Camera();
	Ray CastRay(double x, double y) const;
protected:
private:
	Point position;
	Vec3 view_x;
	Vec3 view_y;
	Vec3 lower_left_corner;
	double w;
};
#endif
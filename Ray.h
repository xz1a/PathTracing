#ifndef _RAY_H_
#define _RAY_H_
#include "Math.h"

class Ray {
public:
	Ray();
	Ray(const Point& p_origin, const Vec3& p_direction);
	~Ray();
	Point GetOrigin() const;
	Vec3 GetDirection() const;
	Point At(double delta_time) const;
protected:
private:
	Point origin;
	Vec3 direction;
};
#endif
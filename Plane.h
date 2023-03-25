#ifndef _PLANE_H_
#define _PLANE_H_
#include "Hittable.h"

class Plane : public Hittable {
public:
	Plane(const Vec3 &p_normal_vector, std::shared_ptr<Material> p_material);
	Plane(const Vec3& p_normal_vector, std::shared_ptr<Material> p_material, const Point& p_position);
	bool CheckHit(const Ray& ray, double time_min, double time_max, HitData& hit_data) const override;
protected:
private:
	Vec3 normal_vector;
	Point position;
};
#endif
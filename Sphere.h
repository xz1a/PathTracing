#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "Math.h"
#include "Hittable.h"
#include <memory>
#include "Material.h"

class Sphere : public Hittable {
public:
	Sphere(double p_radius, std::shared_ptr<Material> p_material);
	Sphere(double p_radius, std::shared_ptr<Material> p_material, const Point& p_position);
	~Sphere();
	double GetRadius() const;
	Vec3 GetCenter() const;
	bool CheckHit(const Ray& ray, double time_min, double time_max, HitData &hit_data) const override;
protected:
private:
	Point position;
	double radius;
};
#endif
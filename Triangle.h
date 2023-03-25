#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include "Math.h"
#include "Hittable.h"

class Triangle : public Hittable {
public:
	Triangle(double p_vertices[9], std::shared_ptr<Material> p_material);
	Triangle(double p_vertices[9], std::shared_ptr<Material> p_material, const Point &p_position);
	~Triangle();
	bool CheckHit(const Ray& ray, double time_min, double time_max, HitData& hit_data) const override;
protected:
private:
	Vec3 position;
	Vec3 vertices[3];
};
#endif
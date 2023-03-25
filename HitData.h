#ifndef _HIT_DATA_H_
#define _HIT_DATA_H_
#include "Vector3.h"
#include "Ray.h"
#include <memory>

class Material;

struct HitData {
	//bool hit;
	bool front_face;
	Vec3 hit_point;
	Vec3 normal_vector;
	double hit_time;
	std::shared_ptr<Material> material;
	void SetNormal(const Ray& ray, const Vec3 &p_normal_vector) {
		front_face = dot(ray.GetDirection(), p_normal_vector) < 0;
		normal_vector = front_face ? p_normal_vector : -p_normal_vector;
	}
};
#endif
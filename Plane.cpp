#include "Plane.h"

Plane::Plane(const Vec3& p_normal_vector, std::shared_ptr<Material> p_material) : Hittable(p_material) {
	position = Point();
	normal_vector = p_normal_vector;
	normal_vector.normalize();
}

Plane::Plane(const Vec3& p_normal_vector, std::shared_ptr<Material> p_material, const Point& p_position) : Plane(p_normal_vector, p_material) {
	position = p_position;
}

bool Plane::CheckHit(const Ray& ray, double time_min, double time_max, HitData& hit_data) const {
	double denom = dot(normal_vector, ray.GetDirection());
	double zero = 1e-8;
	if (fabs(denom) >= zero) {
		
		Vec3 v1 = position - ray.GetOrigin();
		double time = dot(v1, normal_vector) / denom;
		//std::cerr << "plane time: " << time << std::endl << std::flush;
		if (time < zero || time < time_min || time > time_max) {
			return false;
		}
		hit_data.hit_point = ray.At(time);
		hit_data.hit_time = time;
		hit_data.normal_vector = normal_vector;
		hit_data.material = this->material;
		return true;
	}
	return false;
}
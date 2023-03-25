#include "Sphere.h"

Sphere::Sphere(double p_radius, std::shared_ptr<Material> p_material) : radius(p_radius), Hittable(p_material) {
	position = Point();
}

Sphere::Sphere(double p_radius, std::shared_ptr<Material> p_material, const Point& p_position) : Sphere (p_radius, p_material) {
	position = p_position;
}

Sphere::~Sphere() {

}

double Sphere::GetRadius() const {
	return radius;
}

Vec3 Sphere::GetCenter() const {
	return position;
}

bool Sphere::CheckHit(const Ray& ray, double time_min, double time_max, HitData &hit_data) const {
	Vec3 oc = ray.GetOrigin() - position;
	double a = ray.GetDirection().length_squared();
	double half_b = dot(oc, ray.GetDirection());
	double c = oc.length_squared() - (radius * radius);
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0) {
		return false;
	} else {
		double square_root_discriminant = sqrt(discriminant);
		double time = (-half_b - square_root_discriminant) / a;
		if (time < time_min || time >= time_max) {
			time = (-half_b + square_root_discriminant) / a;
			if (time < time_min || time >= time_max) {
				return false;
			}
		}
		hit_data.hit_point = ray.At(time);
		hit_data.hit_time = time;
		hit_data.SetNormal(ray, (hit_data.hit_point - position) / radius);
		hit_data.material = this->material;
	}
	return true;
}
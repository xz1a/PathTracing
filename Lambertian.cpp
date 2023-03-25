#include "Lambertian.h"

Lambertian::Lambertian(const Color3 &p_color) : Material(p_color) {

}

bool Lambertian::ReflectRays(const Ray& source_ray, const HitData& hit_data, Color3& p_color, Ray& reflected_ray) const {
	Vec3 reflect_direction = hit_data.normal_vector + Vec3::random_unit_vector();
	if (reflect_direction.IsZero()) {
		reflect_direction = hit_data.normal_vector;
	}
	reflected_ray = Ray(hit_data.hit_point, reflect_direction);
	p_color = color;
	return true;
}
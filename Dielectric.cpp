#include "Dielectric.h"

Dielectric::Dielectric(const Color3& p_color, float p_refration_index) : Material(p_color), refraction_index(p_refration_index) {

}

bool Dielectric::ReflectRays(const Ray& source_ray, const HitData& hit_data, Color3& p_color, Ray& reflected_ray) const {
    p_color = Color3(1.0, 1.0, 1.0);
    float refraction_ratio = hit_data.front_face ? (1.0 / refraction_index) : refraction_index;

    Vec3 unit_direction = source_ray.GetDirection().normalize();
    float cos_theta = fmin(dot(-unit_direction, hit_data.normal_vector), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, hit_data.normal_vector);
    else
        direction = refract(unit_direction, hit_data.normal_vector, refraction_ratio);

    reflected_ray = Ray(hit_data.hit_point, direction);
    return true;
	return false;
}

float Dielectric::reflectance(float p_cos, float p_refraction_index) const {
    auto r0 = (1 - p_refraction_index) / (1 + p_refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - p_cos), 5);
}
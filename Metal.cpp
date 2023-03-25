#include "Metal.h"

Metal::Metal(const Color3& p_color, double p_fuzz) : Material(p_color), fuzz(p_fuzz < 1.0 ? p_fuzz : 1.0) {

}

bool Metal::ReflectRays(const Ray& source_ray, const HitData& hit_data, Color3& p_color, Ray& reflected_ray) const {
    Vec3 reflected_direction = reflect(source_ray.GetDirection().normalize(), hit_data.normal_vector);
    reflected_ray = Ray(hit_data.hit_point, reflected_direction + fuzz * Vec3::random_in_unit_sphere());
    p_color = color;
    return (dot(reflected_ray.GetDirection(), hit_data.normal_vector) > 0);
}
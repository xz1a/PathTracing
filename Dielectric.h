#ifndef _DIELECTRIC_H_
#define _DIELECTRIC_H_
#include "Material.h"

class Dielectric : public Material {
public:
	Dielectric(const Color3& p_color, float p_refraction_index);
	bool ReflectRays(const Ray& source_ray, const HitData& hit_data, Color3& p_color, Ray& reflected_ray) const override;
protected:
	Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) const {
		auto cos_theta = fmin(dot(-uv, n), 1.0);
		Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
		Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
		return r_out_perp + r_out_parallel;
	}
	float reflectance(float p_cos, float p_refraction_index) const;
private:
	float refraction_index;
};
#endif
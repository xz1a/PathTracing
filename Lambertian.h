#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_
#include "Material.h"

class Lambertian : public Material {
public:
	Lambertian(const Color3 &p_color);
	bool ReflectRays(const Ray& source_ray, const HitData& hit_data, Color3& p_color, Ray& reflected_ray) const override;
protected:
private:
};

#endif
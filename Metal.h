#ifndef _METAL_H_
#define _METAL_H_
#include "Material.h"

class Metal : public Material {
public:
	Metal(const Color3& p_color, double p_fuzz);
	bool ReflectRays(const Ray& source_ray, const HitData& hit_data, Color3& p_color, Ray& reflected_ray) const override;
protected:
private:
	double fuzz;
};
#endif
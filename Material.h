#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "Ray.h"
#include "HitData.h"

class Material {
public:
	Material(const Color3 &p_color);
	virtual bool ReflectRays(const Ray& source_ray, const HitData& hit_data, Color3& color, Ray& reflected_ray) const = 0;
protected:
	Color3 color;
private:
};
#endif
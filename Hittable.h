#ifndef _HITTABLE_H_
#define _HITTABLE_H_
#include "HitData.h"
#include "Math.h"
#include "Ray.h"
#include <memory>

class Hittable {
public:
	Hittable(std::shared_ptr<Material> p_material);
	virtual bool CheckHit(const Ray &ray, double time_min, double time_max, HitData &hit_data) const = 0;
protected:
	std::shared_ptr<Material> material;
private:
};
#endif
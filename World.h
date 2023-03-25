#ifndef _WORLD_H_
#define _WORLD_H_
#include <memory>
#include "Hittable.h"
#include <vector>

class World {
public:
	void Add(std::shared_ptr<Hittable> p_object);
	void Clear();
	bool RayCast(const Ray& p_ray, double p_time_min, double p_time_max, HitData& hit_data) const;
protected:
private:
	std::vector<std::shared_ptr<Hittable>> objects;
};
#endif
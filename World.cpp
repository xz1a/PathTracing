#include "World.h"

void World::Add(std::shared_ptr<Hittable> p_object) {
	objects.push_back(p_object);
}

void World::Clear() {
	objects.clear();
}

bool World::RayCast(const Ray& p_ray, double p_time_min, double p_time_max, HitData& hit_data) const {
	HitData temp;
	bool hit_status = false;
	double current_closest = p_time_max;
	for (std::shared_ptr<Hittable> object : objects) {
		if (object->CheckHit(p_ray, p_time_min, current_closest, temp)) {
			hit_status = true;
			current_closest = temp.hit_time;
			hit_data = temp;
		}
	}
	return hit_status;
}
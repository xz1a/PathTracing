#include "Triangle.h"

Triangle::Triangle(double p_vertices[9], std::shared_ptr<Material> p_material) : Hittable(p_material) {
	position = Point();
	vertices[0] = Vec3(p_vertices[0], p_vertices[1], p_vertices[2]);
	vertices[1] = Vec3(p_vertices[3], p_vertices[4], p_vertices[5]);
	vertices[2] = Vec3(p_vertices[6], p_vertices[7], p_vertices[8]);
}

Triangle::Triangle(double p_vertices[9], std::shared_ptr<Material> p_material, const Point& p_position) : Triangle(p_vertices, p_material) {
	position = p_position;
}

Triangle::~Triangle() {

}

bool Triangle::CheckHit(const Ray& ray, double time_min, double time_max, HitData& hit_data) const {
	Vec3 v1 = vertices[1] - vertices[0];
	Vec3 v2 = vertices[2] - vertices[0];

	Vec3 h = cross(ray.GetDirection(), v2);
	double zero = 1e-8;
	double a = dot(v1, h);

	if (a > -zero && a < zero) {
		return false;
	}

	double f = 1.0 / a;
	Vec3 s = ray.GetOrigin() - vertices[0];
	double u = f * dot(s, h);
	if (u < 0.0 || u > 1.0) {
		return false;
	}

	Vec3 q = cross(s, v1);
	double v = f * dot(ray.GetDirection(), q);
	if (v < 0.0 || u + v > 1.0) {
		return false;
	}

	double time = f * dot(v2, q);
	if (time <= zero || time > time_max || time < time_min) {
		return false;
	}
	hit_data.hit_point = ray.At(time);
	hit_data.hit_time = time;
	hit_data.normal_vector = cross(v1, v2).normalize();
	hit_data.material = this->material;
	return true;
}
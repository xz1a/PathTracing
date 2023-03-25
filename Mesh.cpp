#include "Mesh.h"

Mesh::Mesh(const std::string& p_source_path, std::shared_ptr<Material> p_material) : Hittable(p_material), source_path(p_source_path), position(Vec3(0.0, 0.0, 0.0)) {

}

Mesh::Mesh(const std::string& p_source_path, std::shared_ptr<Material> p_material, const Vec3& p_position) : Hittable(p_material), source_path(p_source_path), position(p_position) {

}

void Mesh::Load() {
	std::ifstream file(source_path, std::ios::in);

	if (!file) {
		std::cerr << source_path << " Open Mesh File Failed.\n" << std::endl;
		return;
	}

	std::string line;
	std::istringstream l;
	Vec3 vec;
	double x, y, z;
	int i1, i2, i3;
	while (std::getline(file, line)) {
		switch (line[0]) {
		case 'v':
			l = std::istringstream(line.substr(2));
			l >> x >> y >> z;
			vec= Vec3(x + position.x(), y + position.y(), z + position.z());
			vertices.push_back(vec);
			break;
		case 'f':
			l = std::istringstream(line.substr(2));
			l >> i1 >> i2 >> i3;
			indices.push_back(i1 - 1);
			indices.push_back(i2 - 1);
			indices.push_back(i3 - 1);
			
			break;
		}
	}
	file.close();
}

bool Mesh::CheckHit(const Ray& ray, double time_min, double time_max, HitData& hit_data) const {
	HitData temp;
	double current_closest = time_max;
	bool hit_state = false;
	for (int i = 0; i < indices.size(); i+=3) {
		if (TriangleHit(ray, time_min, current_closest, temp, indices[i], indices[i+1], indices[i+2])) {
			current_closest = temp.hit_time;
			hit_data = temp;
			hit_state = true;
		}
	}
	return hit_state;
}

bool Mesh::TriangleHit(const Ray& ray, double time_min, double time_max, HitData& hit_data, int i0, int i1, int i2) const {
	Vec3 v1 = vertices[i1] - vertices[i0];
	Vec3 v2 = vertices[i2] - vertices[i0];

	Vec3 h = cross(ray.GetDirection(), v2);
	double zero = 1e-8;
	double a = dot(v1, h);

	if (fabs(a) < zero) {
		return false;
	}

	double f = 1.0 / a;
	Vec3 s = ray.GetOrigin() - vertices[i0];
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
	hit_data.SetNormal(ray, cross(v1, v2).normalize());
	hit_data.material = this->material;
	return true;
}
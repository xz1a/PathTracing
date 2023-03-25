#ifndef _MESH_H_
#define _MESH_H_
#include "Hittable.h"
#include <fstream>
#include <sstream>
#include <string>

class Mesh : public Hittable {
public:
	Mesh(const std::string& p_source_path, std::shared_ptr<Material> p_material);
	Mesh(const std::string& p_source_path, std::shared_ptr<Material> p_material, const Vec3& p_position);
	void Load();
	bool CheckHit(const Ray& ray, double time_min, double time_max, HitData& hit_data) const override;
protected:
	bool TriangleHit(const Ray& ray, double time_min, double time_max, HitData& hit_data, int i0, int i1, int i2) const;
private:
	std::vector<Vec3> vertices;
	std::vector<int> indices;
	Vec3 position;
	std::string source_path;
};
#endif
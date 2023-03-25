#ifndef _UTILS_H_
#define _UTILS_H_
#include <math.h>
#include "Math.h"
#include "Ray.h"
#include "World.h"
#include "Sphere.h"
#include <iostream>
#include "Lambertian.h"
#include "Dielectric.h"
#include "Metal.h"
#include "Plane.h"
#include "Mesh.h"

const double infinity = std::numeric_limits<double>::infinity();

double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

Color3 ray_color(const Ray &ray, const World &world, int depth) {
	if (depth <= 0) {
		return Color3();
	}
	HitData hit_data;
	if (world.RayCast(ray, 0.001, infinity, hit_data)) {
		Ray reflected_ray;
		Color3 color;
		if (hit_data.material->ReflectRays(ray, hit_data, color, reflected_ray)) {
			return color * ray_color(reflected_ray, world, depth - 1);
		}
		return Color3();
	}

	Vec3 unit_direction = ray.GetDirection().normalize();
	double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

Color3 ray_color_loop(const Ray& ray, const World& world, int depth) {
	Ray current_ray = ray;
	Color3 return_value = Color3(1.0, 1.0, 1.0);
	for (int i = 0; i < depth; ++i) {
		HitData hit_data;
		if (world.RayCast(current_ray, 0.001, infinity, hit_data)) {
			Ray reflected_ray;
			Color3 color;
			if (hit_data.material->ReflectRays(current_ray, hit_data, color, reflected_ray)) {
				return_value *= color;
				current_ray = reflected_ray;
			}
			else {
				return Color3();
			}
		}
		else {
			Vec3 unit_direction = ray.GetDirection().normalize();
			double t = 0.5 * (unit_direction.y() + 1.0);
			return return_value * ((1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0));
		}
	}
	return Color3();
}


void WritePixel(std::ostream& out, Color3 &color, unsigned int samples_per_pixel, double gamma) {
	double scale = 1.0 / samples_per_pixel;
	color *= scale;
	color[0] = sqrt(color[0]);
	color[1] = sqrt(color[1]);
	color[2] = sqrt(color[2]);
	out << static_cast<int>(256 * clamp(color[0], 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(color[1], 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(color[2], 0.0, 0.999)) << '\n';
}

World random_scene(int size) {
    World world;

	std::shared_ptr<Material> background_sphere_material = std::make_shared<Metal>(Color3(0.7, 0.6, 0.5), 0.0);
	world.Add(std::make_shared<Sphere>(2.0, background_sphere_material, Point(0.0, 2.0, -2*size + 1.5)));
	std::shared_ptr<Material> ground_material = std::make_shared<Metal>(Color3(0.8, 0.8, 0.8), 0.0);

    for (int a = -size; a < size; ++a) {
        for (int b = -size; b < size; ++b) {
            auto choose_mat = random_double();
            Point center(2.0*a + 0.5 * random_double(), 1.0, 2.0 * b + 5.0 * random_double());

			std::shared_ptr<Material> mesh_material;

			if (choose_mat < 0.8) {
				// diffuse
				auto albedo = Color3::random() * Color3::random();
				mesh_material = std::make_shared<Lambertian>(albedo);
			}
			else if (choose_mat < 0.95) {
				// metal
				auto albedo = Color3::random(0.5, 1);
				auto fuzz = random_double(0, 0.5);
				mesh_material = std::make_shared<Metal>(albedo, fuzz);
			}
			else {
				// glass
				auto albedo = Color3();
				mesh_material = std::make_shared<Dielectric>(albedo, 1.5);
			}

			auto choose_shape = random_double();
			if (choose_shape < 0.65) {
				auto random_size = random_double();
				Sphere sphere = Sphere(random_size, mesh_material, center);
				world.Add(std::make_shared<Sphere>(sphere));
			}
			else if (choose_shape < 0.8) {
				Mesh mesh = Mesh("cube.obj", mesh_material, center);
				mesh.Load();
				world.Add(std::make_shared<Mesh>(mesh));
			}
			else if (choose_shape < 0.95) {
				Mesh mesh = Mesh("cylinder.obj", mesh_material, center);
				mesh.Load();
				world.Add(std::make_shared<Mesh>(mesh));
			}
			else {
				Mesh mesh = Mesh("cone.obj", mesh_material, center);
				mesh.Load();
				world.Add(std::make_shared<Mesh>(mesh));
			}
        }
    }

    return world;
}
#endif
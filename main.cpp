#include <iostream>
#include "Math.h"
#include "Utils.h"
#include "Camera.h"
#include "Triangle.h"
#include "Plane.h"
#include "World.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Mesh.h"

const int width = 848, height = 480;
const double aspect_ratio = (double)width / (double)height;
const int samples_per_pixel = 50;
const int max_depth = 25;
World world;
Camera camera = Camera(45, aspect_ratio, 1.0, 100, Vec3(0.0, 2.5, 20.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));

void Setup() {
	world = random_scene(4);
}

void Render() {
	std::cout << "P3\n" << width << ' ' << height << "\n255\n";
	for (int j = height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < width; ++i) {
			Color3 color = Color3();
			for (int k = 0; k < samples_per_pixel; ++k) {
				double x = double(i + random_double()) / (double)(width - 1);
				double y = double(j + random_double()) / (double)(height - 1);
				color += ray_color(camera.CastRay(x, y), world, max_depth);
			}
			WritePixel(std::cout, color, samples_per_pixel, 2.0);
		}
	}
}

int main(int argc, char* argv[]) {
	Setup();
	Render();
	std::cerr << "\nDone.\n";
	return 0;
}
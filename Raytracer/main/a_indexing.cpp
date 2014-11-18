#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/kdtree.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/groups/simplegroup.h>
#include <rt/solids/triangle.h>
#include <iostream>
#include <time.h>

using namespace rt;

#define SAH false

void a_indexing() {
	Image img(800, 600);

	//SimpleGroup* scene = new SimpleGroup();
	BVH* scene = new BVH();
	//timing
	std::cout << "starting clock\n";
	unsigned int start = clock() / 1000;

	scene->add(new Sphere(Point(2.5f, .5f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(2.5f, -1.f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(4.5f, .5f, -1), 0.5, nullptr, nullptr));

	loadOBJ(scene, "models/", "cow.obj");
	if (SAH) {
		loadOBJ(scene, "models/", "ak47.obj");
		loadOBJ(scene, "models/", "cart.obj");
	}

	scene->rebuildIndex();
	World world;
	world.scene = scene;

	unsigned int buildTime = clock() / 1000;
	std::cout << "time to add and build index: " << ((buildTime - start) / 1000) << "s\n";

	RayCastingIntegrator integrator(&world);

	if (!SAH) {
		PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f, 1.0f, -0.6f), Vector(0, 0, 1), pi / 8, pi / 6);
		Renderer engine1(&cam1, &integrator);
		engine1.render(img);
		img.writePNG("a3-1.png");
	} else {
		PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f) - 100 * Vector(1.0f, 1.0f, -0.6f), Vector(1.0f, 1.0f, -0.6f),
				Vector(0, 0, 1), pi / 8, pi / 6);
		Renderer engine1(&cam1, &integrator);
		engine1.render(img);
		img.writePNG("a3-1.png");
	}
	PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f) - Point(16.065f, -12.506f, 1.771f),
			Vector(0, 0, 1), pi / 8, pi / 6);

	unsigned int renderImage1 = clock() / 1000;
	std::cout << "time to render image 1: " << ((renderImage1 - buildTime) / 1000) << "s\n";

	Renderer engine2(&cam2, &integrator);
	engine2.render(img);
	img.writePNG("a3-2.png");

	unsigned int renderImage2 = clock() / 1000;
	std::cout << "time to render image 2: " << ((renderImage2 - renderImage1) / 1000) << "s\n";

	std::cout << "total time: " << ((renderImage2 - start) / 1000) << "s\n";

}

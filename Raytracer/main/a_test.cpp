/*
 * a_test.cpp
 *
 *  Created on: 21.01.2015
 *      Author: chris
 */

#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>

#include <cmath>
#include <math.h>

#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/cameras/perspective.h>

#include <rt/coordmappers/plane.h>

#include <rt/groups/bvh.h>
#include <rt/groups/csg.h>
#include <rt/groups/simplegroup.h>

#include <rt/integrators/raytrace.h>
#include <rt/integrators/recraytrace.h>
#include <rt/integrators/rayMarching.h>

#include <rt/lights/directional.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>

#include <rt/loaders/obj.h>

#include <rt/materials/combine.h>
#include <rt/materials/dummy.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <rt/materials/mirror.h>
#include <rt/materials/phong.h>

#include <rt/primmod/instance.h>

#include <rt/solids/fracLand.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/sphere.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/mountain.h>
#include <rt/textures/perlin.h>
#include <rt/textures/star.h>

#include <rt/integrators/casting.h>


using namespace rt;

void a_test() {
	Image img(800, 600);
	World world;
	BVH* scene = new BVH();

	Point camPoint = Point(0.f, 0.f, -100.f);
	PerspectiveCamera cam = PerspectiveCamera(camPoint, Vector(0, 0, 1), Vector(0, 1, 0), 0.686f,
			0.686f * (4.f / 3.f));

	/*Point camPoint = Point(0.f, 0.f, -20.f);
	PerspectiveCamera cam = PerspectiveCamera(camPoint, Vector(0, 0, 1), Vector(0, -1, 0), 0.686f,
			0.686f * (4.f / 3.f));
*/
	MatLib materialLibrary;
	BVH* heli = new BVH();
	loadOBJ(heli, "models/Bell407/", "bell407-cut.obj", &materialLibrary);
	heli->rebuildIndex();

	Instance* in = new Instance(heli);

	in->scale(5.f);
	in->rotate(Vector(1, 0, 0), 3 * M_PI / 2);
	in->rotate(Vector(0, 1, 0), -9 * M_PI / 14);
	in->rotate(Vector(1, 0, 0), -M_PI / 7);
	in->rotate(Vector(0, 1, 0), -M_PI / 7);
	//in->translate(Vector(15.0f, 50.f, 80.f));

	scene->add(heli);

	scene->rebuildIndex();

	world.scene = in;


	world.light.push_back(new DirectionalLight(Vector(0, 0, 1), RGBColor(1, 1, 1)));
	world.light.push_back(new DirectionalLight(Vector(0, 1, 0), RGBColor(1, 1, 1)));
	world.light.push_back(new DirectionalLight(Vector(1, 0, 0), RGBColor(1, 1, 1)));
	world.light.push_back(new DirectionalLight(Vector(0, 0, -1), RGBColor(1, 1, 1)));
	world.light.push_back(new DirectionalLight(Vector(0, -1, 0), RGBColor(1, 1, 1)));
	world.light.push_back(new DirectionalLight(Vector(-1, 0, 0), RGBColor(1, 1, 1)));

	//RayCastingIntegrator integrator(&world);
//	RecursiveRayTracingIntegrator integrator(&world);
	//RayTracingIntegrator integrator(&world);
	RayMarchingIntegrator integrator(&world);
	Renderer engine(&cam, &integrator);
	engine.render(img);
	engine.setSamples(30);
	img.writePNG("test.png");
}

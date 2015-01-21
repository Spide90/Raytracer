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
	Image img(800, 800);
	World world;
	BVH* scene = new BVH();

	Point camPoint = Point(0.f, 10.f, -50.f);
	PerspectiveCamera cam(camPoint, Vector(0, 0, 1), Vector(0, 1, 0), 0.686f,
			0.686f);

	MatLib materialLibrary;
	loadOBJ(scene, "models/", "Tree_V10_Final.obj", &materialLibrary);

	scene->rebuildIndex();

	world.scene = scene;

	world.light.push_back(new DirectionalLight(Vector(0, 0, 1), RGBColor(1, 1, 1)));

	//RayCastingIntegrator integrator(&world);
	//	RecursiveRayTracingIntegrator integrator(&world);
	RayTracingIntegrator integrator(&world);
	Renderer engine(&cam, &integrator);
	engine.render(img);
	img.writePNG("test.png");
}

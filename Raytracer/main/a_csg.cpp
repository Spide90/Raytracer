/*
 * a_csg.cpp
 *
 *  Created on: 12.12.2014
 *      Author: chris
 */

#include <core/image.h>
#include <rt/cameras/perspective.h>
#include <rt/groups/group.h>
#include <rt/groups/simplegroup.h>
#include <rt/primmod/instance.h>
#include <rt/integrators/casting.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <core/point.h>

#include <rt/groups/csg.h>

#include <rt/solids/infiniteplane.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/solids/aabox.h>

using namespace rt;

void a_csg() {
	Image img(800, 600);

	ConstructiveSolidGeometry* scene = new ConstructiveSolidGeometry(
			ConstructiveSolidGeometry::UNION);


	scene->add(new AABox(Point(0, 0, 0), Point(10, 10, 10), nullptr, nullptr));
	scene->add(new Sphere(Point(10, 10, 10), 5, nullptr, nullptr));

	World world;
	world.scene = scene;
	RayCastingIntegrator integrator(&world);

	PerspectiveCamera cam(Point(-3.75f, 20, 40), Vector(0.1, -0.5, -1),
			Vector(0, 1, 0), pi / 4, pi / 3);
	Renderer engine(&cam, &integrator);
	engine.render(img);
	img.writePNG("a7-2-union.png");

	scene = new ConstructiveSolidGeometry(
			ConstructiveSolidGeometry::INTERSECTION);


	scene->add(new AABox(Point(0, 0, 0), Point(10, 10, 10), nullptr, nullptr));
	scene->add(new Sphere(Point(10, 10, 10), 5, nullptr, nullptr));

	world.scene = scene;

	engine.render(img);
	img.writePNG("a7-2-intersection.png");

	scene = new ConstructiveSolidGeometry(
			ConstructiveSolidGeometry::DIFFERENCE);


	scene->add(new AABox(Point(0, 0, 0), Point(10, 10, 10), nullptr, nullptr));
	scene->add(new Sphere(Point(10, 10, 10), 5, nullptr, nullptr));

	world.scene = scene;

	engine.render(img);
	img.writePNG("a7-2-difference.png");

}


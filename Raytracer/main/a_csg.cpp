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

#include <rt/groups/csg.h>

#include <rt/solids/infiniteplane.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>


using namespace rt;

void makeBox(Group* scene, const Point& aaa, const Vector& forward, const Vector& left, const Vector& up) {
    scene->add(new Quad(aaa, forward, left, nullptr, nullptr));
    scene->add(new Quad(aaa, forward, up, nullptr, nullptr));
    scene->add(new Quad(aaa, left, up, nullptr, nullptr));
    Point bbb = aaa + forward + left + up;
    scene->add(new Quad(bbb, -forward, -left, nullptr, nullptr));
    scene->add(new Quad(bbb, -forward, -up, nullptr, nullptr));
    scene->add(new Quad(bbb, -left, -up, nullptr, nullptr));
}

void a_csg() {
    Image img(800, 600);

    ConstructiveSolidGeometry* scene = new ConstructiveSolidGeometry(ConstructiveSolidGeometry::INTERSECTION);

    SimpleGroup* box = new SimpleGroup();

    float size = 5;

    makeBox(box, Point(1, 1, 1), Vector(0, 0, size), Vector(size, 0, 0), Vector(0, size, 0));

    scene->add(new Sphere(Point(size, size, size), size/2, nullptr, nullptr));

    scene->add(box);

    //scene->add(new InfinitePlane(Point(0,0,0), Vector(0, 1, 0), nullptr, nullptr));

    World world;
    world.scene = scene;
    RayCastingIntegrator integrator(&world);

    PerspectiveCamera cam(Point(-3.75f, 20, 40), Vector(0.1, -0.5, -1), Vector(0, 1, 0), pi/4, pi/3);
    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG("a7-2.png");
}




/*
 * a_volume.cpp
 *
 *  Created on: 22.01.2015
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
#include <rt/lights/ambient.h>

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
#include <rt/solids/quad.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/mountain.h>
#include <rt/textures/perlin.h>
#include <rt/textures/star.h>

#include <rt/integrators/casting.h>
#include <rt/integrators/volumeRaytrace.h>
#include <rt/integrators/rayMarching.h>

#include <rt/volume/AmbientHomogenious.h>
#include <rt/volume/homogenious.h>
#include <rt/volume/heterogenious.h>

using namespace rt;

#define AMBIENT_HOMOGENIOUS true
#define HOMOGENIOUS false
#define HETEROGENIOUS false

void a_volume() {
	Image img(800, 800);
	World world;
	BVH* scene = new BVH();

	Point camPoint = Point(0.f, 0.f, -40.f);
	PerspectiveCamera cam(camPoint, Vector(0, 0.f, 1), Vector(0, 1, 0), 0.686f, 0.686f);

	Texture* redtex = new ConstantTexture(RGBColor(.7f, 0.f, 0.f));
	Texture* greentex = new ConstantTexture(RGBColor(0.f, .7f, 0.f));
	Texture* bluetex = new ConstantTexture(RGBColor(0.f, 0.f, 0.7f));
	Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
	Texture* yellowtex = new ConstantTexture(RGBColor(.7f, .7f, 0));
	Texture* pinktex = new ConstantTexture(RGBColor(0.7f, 0, 0.35f));
	Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));

	Material* whiteMaterial = new LambertianMaterial(blacktex, whitetex);
	Material* redMaterial = new LambertianMaterial(blacktex, redtex);
	Material* greenMaterial = new LambertianMaterial(blacktex, greentex);
	Material* blueMaterial = new LambertianMaterial(blacktex, bluetex);
	Material* yellowMaterial = new LambertianMaterial(blacktex, yellowtex);
	Material* pinkMaterial = new LambertianMaterial(blacktex, pinktex);

	//back
	scene->add(new Quad(Point(-10, -10, 10), Vector(20, 0, 0), Vector(0, 20, 0), nullptr, redMaterial));
	//top
	scene->add(new Quad(Point(-10, 10, 10), Vector(20, 0, 0), Vector(0, 0, -20), nullptr, blueMaterial));
	//left
	scene->add(new Quad(Point(-10, -10, 10), Vector(0, 20, 0), Vector(0, 0, -20), nullptr, greenMaterial));
	//bottom
	scene->add(new Quad(Point(-10, -10, 10), Vector(20, 0, 0), Vector(0, 0, -20), nullptr, yellowMaterial));
	//right
	scene->add(new Quad(Point(10, -10, 10), Vector(0, 20, 0), Vector(0, 0, -20), nullptr, pinkMaterial));

	scene->add(new Sphere(Point(5, 5, 5), 3, nullptr, whiteMaterial));

	scene->rebuildIndex();

	world.scene = scene;

	Fog* fog;
	Integrator* integrator;

	if (AMBIENT_HOMOGENIOUS) {
		fog = new AmbientHomogeniousFog(scene, 0.025, RGBColor::rep(0.5));
		integrator = new VolumeRaytracingIntegrator(&world);
	}
	if (HOMOGENIOUS) {
//		fog = new HomogeniousFog(scene, 0.025, whiteMaterial);
		integrator = new RayMarchingIntegrator(&world);
	}
	if (HETEROGENIOUS) {
		PerlinTexture* perlinTex = new PerlinTexture(RGBColor(1.0f, 1.0f, 0.9f), RGBColor(0.5f, 0.5f, 1.0f));
		perlinTex->addOctave(0.5f, 5.0f);
		perlinTex->addOctave(0.25f, 10.0f);
		perlinTex->addOctave(0.125f, 20.0f);
		perlinTex->addOctave(0.125f, 40.0f);
		LambertianMaterial* perlin = new LambertianMaterial(blacktex, perlinTex);

		fog = new HeterogeniousFog(scene, whiteMaterial);
		integrator = new RayMarchingIntegrator(&world);
	}

	world.fog = fog;

	//world.ambientLight = new AmbientLight(RGBColor(1, 1, 1));
	world.light.push_back(new PointLight(Point(-5, -5, -5), RGBColor(200, 200, 200)));
	//world.light.push_back(new DirectionalLight(Vector(0, 0, 1), RGBColor(1, 1, 1)));

	//RecursiveRayTracingIntegrator integrator(&world);
	//RayTracingIntegrator integrator(&world);
	Renderer engine(&cam, integrator);
	engine.render(img);
	img.writePNG("volume.png");
}


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

using namespace rt;

void a_rendComp() {
	Image img(800, 800);
	World world;
//	SimpleGroup* scene = new SimpleGroup();
	BVH* scene = new BVH();

	Point camPoint = Point(0.f, 50.f, -20.f);
	PerspectiveCamera cam(camPoint, Vector(0, 0, 1), Vector(0, 1, 0), 0.686f,
			0.686f);

	//The Sea
	{
		Material* sea = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.01f);
		scene->add(
			new InfinitePlane(Point(0.0f, 30.0f, 0.018), Vector(0.f, 1.f, 0.f),
					nullptr, sea));
	}



	//The Sun
	{
		DummyMaterial* dummy = new DummyMaterial();
		Point center = Point(-18000.f, 22000.f, 100000.f);
		Vector vec = (center - camPoint).normalize();
		vec = vec / vec.z;
		float radius = 4000.f;
		scene->add(new Sphere(center, radius, nullptr, dummy));
		float scale = 40000000.f;
		world.light.push_back(
				new PointLight(camPoint + (100000.f - radius - 2000.f) * vec,
						RGBColor(253.f * scale / 255.f, 184.f * scale / 255.f,
								19.f * scale / 255.f)));
	}

	//The Landscape
	{
		ConstantTexture* blackTex = new ConstantTexture(
				RGBColor(0.f, 0.f, 0.f));
		MountainTexture* landTex = new MountainTexture();
		Material* landscape = new LambertianMaterial(blackTex, landTex);
		scene->add(
				new FracLand(Point(800.f, 0.f, 1000.f),
						Point(-800.f, 0.f, 1000.f), Point(0.f, 0.f, 0.f), 12,
						0.55, 125.f,
						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
							Vector(-1.f, 0.0f, 1.f)), landscape));
		world.light.push_back(
				new PointLight(Point(0.f, 1000.f, 0.f),
						RGBColor(253.f * 3000000.f / 255.f,
								253.f * 3000000.f / 255.f,
								253.f * 3000000.f / 255.f)));
	}

	//The Moon
	{
		DummyMaterial* moonMat = new DummyMaterial();
		ConstructiveSolidGeometry* csg1 = new ConstructiveSolidGeometry(
				ConstructiveSolidGeometry::DIFFERENCE);
		csg1->add(
				new Sphere(Point(400.f, 400.f, 2000.f), 70.f, nullptr,
						moonMat));
		csg1->add(
				new Sphere(Point(403.f, 412.f, 1970.f), 70.f, nullptr,
						moonMat));
		scene->add(csg1);
//	scene->add(new Sphere(Point(400.f, 400.f, 2000.f), 70.f, nullptr, moonMat));
		world.light.push_back(
				new SpotLight(Point(200.f, 0.f, 2000.f),
						Vector(1.0f, 4.0f, 0.0f), pi / 3, 8.0f,
						RGBColor(400000.f, 400000.f, 400000.f)));
	}

	//The stars
	{
		StarTexture* starTex = new StarTexture();
		ConstantTexture* blackTex = new ConstantTexture(
				RGBColor(0.f, 0.f, 0.f));
		Material* stars = new LambertianMaterial(blackTex, starTex);
		scene->add(
				new InfinitePlane(Point(0.f, 0.f, 1000000.f),
						Vector(0.f, 0.f, -1.f), nullptr, stars));
	}

	//DEBUG LIGHT
//	world.light.push_back(new DirectionalLight(Vector(0.f, -100.f, 100.f), RGBColor(253.f/ 255.f, 253.f / 255.f, 253.f / 255.f)));

	world.scene = scene;
	RecursiveRayTracingIntegrator integrator(&world);
//	RayTracingIntegrator integrator(&world);
	Renderer engine(&cam, &integrator);
	engine.render(img);
	img.writePNG("rendComp.png");
}

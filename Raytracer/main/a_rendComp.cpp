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

#include <rt/lights/ambient.h>
#include <rt/lights/directional.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>

#include <rt/loaders/obj.h>

#include <rt/materials/combine.h>
#include <rt/materials/dummy.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <rt/materials/mirror.h>
#include <rt/materials/phong.h>

#include <rt/primmod/instance.h>

#include <rt/solids/disc.h>
#include <rt/solids/fracLand.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/mountain.h>
#include <rt/textures/perlin.h>
#include <rt/textures/star.h>

using namespace rt;

void a_rendComp() {
	Image img(800, 600);
	World world;
//	SimpleGroup* scene = new SimpleGroup();
	BVH* scene = new BVH();

	Point camPoint = Point(-0.3f, 53.5f, -20.f);
	PerspectiveCamera cam(camPoint, Vector(0, 0, 1), Vector(0, 1, 0), 0.686f,
			0.686f * (4.f / 3.f));

//	The Sea
	{
		ConstantTexture* groundTex = new ConstantTexture(
				RGBColor(25.f, 25.f, 112.f) * (1 / 255.f));
		PerlinTexture* perlinTex = new PerlinTexture(
				RGBColor(28.0f, 32.0f, 36.0f) * (1 / 255.f),
				RGBColor(25.f, 25.f, 112.f) * (1 / 255.f));
		perlinTex->addOctave(0.5f, 5.0f);
		perlinTex->addOctave(0.25f, 10.0f);
		perlinTex->addOctave(0.125f, 20.0f);
		perlinTex->addOctave(0.125f, 40.0f);
		Material* seaGround = new LambertianMaterial(perlinTex, groundTex);
		Material* FuzMirSea = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.01f);
		Material* GlassSea = new GlassMaterial(2.f);
		CombineMaterial* sea = new CombineMaterial();
		sea->add(FuzMirSea, 0.82f);
		sea->add(GlassSea, 0.18f);
		scene->add(
				new InfinitePlane(Point(0.0f, 30.0f, 0.018),
						Vector(0.f, 1.f, 0.f), nullptr, sea));
		scene->add(
				new InfinitePlane(Point(0.0f, 10.0f, 0.018),
						Vector(0.f, 1.f, 0.f), nullptr, seaGround));

	}

//The Sun
	{
		DummyMaterial* dummy = new DummyMaterial();
		Point center = Point(-18000.f, 26000.f, 100000.f);
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
//		scene->add(
//				new FracLand(Point(800.f, 0.f, 1000.f),
//						Point(-800.f, 0.f, 1000.f), Point(0.f, 0.f, 0.f), 12,
//						0.55, 125.f,
//						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
//							Vector(-1.f, 0.0f, 1.f)), landscape));
//		BVH* leftMountainGroup = new BVH();
//		leftMountainGroup->add(
//				new FracLand(Point(20.f, 20.f, 0.f), Point(-10.f, 20.f, 0.f),
//						Point(-10.f, 20.f, -40.f), 12, 0.5f, 60.f,
//						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
//								Vector(-1.f, 0.0f, 1.f)), landscape));
//		Instance *leftMountain = new Instance(leftMountainGroup);
//		leftMountain->translate(Vector(1.6f, 0.f, 0.f));
//		scene->add(leftMountain);
//		BVH* rightMountainGroup = new BVH();
//		rightMountainGroup->add(
//				new FracLand(Point(-30.f, 20.f, 0.f), Point(0.f, 20.f, 0.f),
//						Point(-10.f, 20.f, -40.f), 12, 0.5f, 60.f,
//						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
//								Vector(-1.f, 0.0f, 1.f)), landscape));
//		Instance *rightMountain = new Instance(rightMountainGroup);
//		rightMountain->translate(Vector(-3.3f, 0.f, 0.f));
//		scene->add(rightMountain);
//		world.light.push_back(
//				new PointLight(Point(-0.5f, 53.5f, -20.f),
//						RGBColor(253.f * 400.f / 255.f, 253.f * 400.f / 255.f,
//								253.f * 400.f / 255.f)));
//		world.light.push_back(
//				new PointLight(Point(-2.f, 53.5f, -5.f),
//						RGBColor(253.f * 300.f / 255.f, 253.f * 300.f / 255.f,
//								253.f * 300.f / 255.f)));
		world.light.push_back(
				new PointLight(Point(0.f, 1000.f, 0.f),
						RGBColor(253.f * 3000000.f / 255.f,
								253.f * 3000000.f / 255.f,
								253.f * 3000000.f / 255.f)));
	}

//The Landscape 2
//	{
//		ConstantTexture* blackTex = new ConstantTexture(
//				RGBColor(0.f, 0.f, 0.f));
//		MountainTexture* landTex = new MountainTexture();
//		Material* landscape = new LambertianMaterial(blackTex, landTex);
//		float yScale = 20.f;
//		scene->add(
//				new FracLand(Point(800.f, yScale, 1000.f),
//						Point(-100.f, yScale, 1000.f), Point(0.f, yScale, 0.f), 12,
//						0.55, 125.f,
//						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
//								Vector(-1.f, 0.0f, 1.f)), landscape));
//		scene->add(
//				new FracLand(Point(-30.f, yScale, 300.f),
//						Point(-300.f, yScale, 300.f), Point(0.f, yScale, 0.f), 12,
//						0.55, 125.f,
//						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
//								Vector(-1.f, 0.0f, 1.f)), landscape));
//		scene->add(
//				new Quad(Point(-30.f, yScale, 300.f), Vector(-770.f, 0.f, 0.f),
//						Vector(-70.f, 0.f, 700.f),
//						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
//								Vector(-1.f, 0.0f, 1.f)), landscape));
//		world.light.push_back(
//				new PointLight(Point(0.f, 1000.f, 0.f),
//						RGBColor(253.f * 3000000.f / 255.f,
//								253.f * 3000000.f / 255.f,
//								253.f * 3000000.f / 255.f)));
//	}

//The Moon
	{
		DummyMaterial* moonMat = new DummyMaterial();
		ConstantTexture* blueTex = new ConstantTexture(
				RGBColor(0.02f, 0.02f, 0.96f));
		ConstantTexture* blackTex = new ConstantTexture(
				RGBColor(0.f, 0.f, 0.f));
		ConstantTexture* redTex = new ConstantTexture(
				RGBColor(0.96f, 0.02f, 0.02f));
		Material* moonMat1 = new LambertianMaterial(blackTex, redTex);
		Material* moonMat2 = new LambertianMaterial(blueTex, redTex);
		ConstructiveSolidGeometry* csg1 = new ConstructiveSolidGeometry(
				ConstructiveSolidGeometry::DIFFERENCE);
		Point center1 = Point(4000.f, 4000.f, 20000.f);
		Point center2 = Point(4100.f, 4060.f, 19700.f);
		Vector vec = (center1 - center2);
		csg1->add(new Sphere(center1, 700.f, nullptr, moonMat1));
		csg1->add(new Sphere(center2, 700.f, nullptr, moonMat));
		scene->add(csg1);
		Vector camTOmoon = (center1 - camPoint) / (center1.z - camPoint.z);
		Point discCenter = camPoint + 50000.f * camTOmoon
				+ Vector(-40.f, -40.f, 0);
		scene->add(
				new Disc(discCenter, -camTOmoon.normalize(), 1800.f, nullptr,
						moonMat1));
		world.light.push_back(
				new SpotLight(camPoint + 49500.f * camTOmoon,
						discCenter - (camPoint + 49500.f * camTOmoon), pi,
						0.25f, RGBColor::rep(253.f * 20000000.f / 255.f)));
//		scene->add(new Sphere((center1 + 1500.f * vec.normalize()), 700.f, nullptr, moonMat2));
//		world.light.push_back(new SpotLight((center1 + 1500.f * vec.normalize()), -vec.normalize(), pi, 0.25f,
//				RGBColor::rep(253.f * 5000000000.f / 255.f)));
		Vector sLight = Vector(-1.f, -1.f, 0.f).normalize();
		world.light.push_back(
				new PointLight(
						(center1 + sLight * 2000 + Vector(0.f, 0.f, 1000.f)),
						RGBColor::rep(253.f * 5000000.f / 255.f)));
		Vector sLight1 = Vector(0.f, -1.f, 0.f).normalize();
		world.light.push_back(
				new PointLight(
						(center1 + sLight1 * 2000 + Vector(0.f, 0.f, 2000.f)),
						RGBColor::rep(253.f * 12000000.f / 255.f)));
		Vector sLight2 = Vector(-1.f, 0.f, 0.f).normalize();
		world.light.push_back(
				new PointLight(
						(center1 + sLight2 * 2000 + Vector(0.f, 0.f, 0.f)),
						RGBColor::rep(253.f * 2000000.f / 255.f)));

//		world.light.push_back(
//				new SpotLight((center1 + sLight * 2000 + Vector(0.f, 0.f, 100.f)), -sLight, pi, 0.25f,
//						RGBColor::rep(253.f * 10000000.f / 255.f)));
//		world.light.push_back(
//				new PointLight(camPoint + 1900 * (center1 - camPoint).normalize() + Vector(0.f, -10.f, 0.f),
//						RGBColor(253.f * 1000.f / 255.f,
//								253.f * 1000.f / 255.f,
//								253.f * 1000.f / 255.f)));
//		world.light.push_back(
//				new PointLight(camPoint + 2100 * (center1 - camPoint).normalize() + Vector(0.f, -10.f, 0.f),
//						RGBColor(253.f * 1000.f / 255.f,
//								253.f * 1000.f / 255.f,
//								253.f * 1000.f / 255.f)));
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
//	world.light.push_back(new DirectionalLight(vec, RGBColor(253.f/ 255.f, 253.f / 255.f, 253.f / 255.f)));
//	world.light.push_back(
//			new DirectionalLight(Vector(0.f, -1.f, 0.f),
//					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
//	world.light.push_back(
//			new DirectionalLight(Vector(0.f, 1.f, 0.f),
//					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
//	world.light.push_back(
//			new DirectionalLight(Vector(1.f, 0.f, 0.f),
//					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
//	world.light.push_back(
//			new DirectionalLight(Vector(-1.f, 0.f, 0.f),
//					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
//	world.light.push_back(
//			new DirectionalLight(Vector(0.f, 0.f, -1.f),
//					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
//	world.light.push_back(
//			new DirectionalLight(Vector(0.f, 0.f, 1.f),
//					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));

	//The Tree(s)
	{
		loadOBJ(scene, "models/", "cow.obj");
	}

	world.scene = scene;
	RecursiveRayTracingIntegrator integrator(&world);
//	RayTracingIntegrator integrator(&world);
	Renderer engine(&cam, &integrator);
	engine.render(img);
	img.writePNG("rendComp.png");
}

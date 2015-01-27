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

#include <rt/integrators/rayMarching.h>
#include <rt/integrators/raytrace.h>
#include <rt/integrators/recraytrace.h>
#include <rt/integrators/volumeRaytrace.h>

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

#include <rt/volume/AmbientHomogenious.h>
#include <rt/volume/homogenious.h>

using namespace rt;

#define SEA true
#define SUN true
#define LANDSCAPE false
#define MOON true
#define STARS true
#define DEBUGLIGHT false

void a_rendComp() {
	Image img(800, 600);
	World world;
	BVH* scene = new BVH();
	BVH* TheSea = new BVH();
	BVH* TheSun = new BVH();
	BVH* TheLandscape = new BVH();
	BVH* TheMoon = new BVH();
	BVH* TheStars = new BVH();

	Point camPoint = Point(-0.3f, 53.5f, -20.f);
	PerspectiveCamera cam(camPoint, Vector(0, 0, 1), Vector(0, 1, 0), 0.686f,
			0.686f * (4.f / 3.f));

//	The Sea
	if(SEA)
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
		TheSea->add(
				new InfinitePlane(Point(0.0f, 30.0f, 0.018),
						Vector(0.f, 1.f, 0.f), nullptr, sea));
		TheSea->add(
				new InfinitePlane(Point(0.0f, 10.0f, 0.018),
						Vector(0.f, 1.f, 0.f), nullptr, seaGround));

	}

//The Sun
	if(SUN)
	{
		DummyMaterial* dummy = new DummyMaterial();
		Point center = Point(-18000.f, 26000.f, 100000.f);
		Vector vec = (center - camPoint).normalize();
		vec = vec / vec.z;
		float radius = 4000.f;
		TheSun->add(new Sphere(center, radius, nullptr, dummy));
		float scale = 40000000.f;
		world.light.push_back(
				new PointLight(camPoint + (100000.f - radius - 2000.f) * vec,
						RGBColor(253.f * scale / 255.f, 184.f * scale / 255.f,
								19.f * scale / 255.f)));
	}

	//The Landscape
	if(LANDSCAPE)
	{
		ConstantTexture* blackTex = new ConstantTexture(
				RGBColor(0.f, 0.f, 0.f));
		MountainTexture* landTex = new MountainTexture();
		Material* landscape = new LambertianMaterial(blackTex, landTex);
		TheLandscape->add(
				new FracLand(Point(800.f, 0.f, 1000.f),
						Point(-800.f, 0.f, 1000.f), Point(0.f, 0.f, 0.f), 12,
						0.55, 125.f,
						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
							Vector(-1.f, 0.0f, 1.f)), landscape));
		BVH* leftMountainGroup = new BVH();
		leftMountainGroup->add(
				new FracLand(Point(20.f, 20.f, 0.f), Point(-10.f, 20.f, 0.f),
						Point(-10.f, 20.f, -40.f), 12, 0.5f, 60.f,
						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
								Vector(-1.f, 0.0f, 1.f)), landscape));
		Instance *leftMountain = new Instance(leftMountainGroup);
		leftMountain->translate(Vector(1.6f, 0.f, 0.f));
		TheLandscape->add(leftMountain);
		BVH* rightMountainGroup = new BVH();
		rightMountainGroup->add(
				new FracLand(Point(-30.f, 20.f, 0.f), Point(0.f, 20.f, 0.f),
						Point(-10.f, 20.f, -40.f), 12, 0.5f, 60.f,
						new PlaneCoordMapper(Vector(1.f, 0.0f, 1.f),
								Vector(-1.f, 0.0f, 1.f)), landscape));
		Instance *rightMountain = new Instance(rightMountainGroup);
		rightMountain->translate(Vector(-3.3f, -7.5f, 0.f));
		TheLandscape->add(rightMountain);
		world.light.push_back(
				new PointLight(Point(-0.5f, 53.5f, -20.f),
						RGBColor(253.f * 400.f / 255.f, 253.f * 400.f / 255.f,
								253.f * 400.f / 255.f)));
		world.light.push_back(
				new PointLight(Point(-2.f, 53.5f, -5.f),
						RGBColor(253.f * 300.f / 255.f, 253.f * 300.f / 255.f,
								253.f * 300.f / 255.f)));
		world.light.push_back(
				new PointLight(Point(0.f, 1000.f, 0.f),
						RGBColor(253.f * 3000000.f / 255.f,
								253.f * 3000000.f / 255.f,
								253.f * 3000000.f / 255.f)));
	}

//The Moon
	if(MOON)
	{
		Point moonCenter = Point(4000.f, 4000.f, 20000.f);
		float moonRadius = 700.f;
		Material* moonMat = new GlassMaterial(2.f);
		TheMoon->add(new Sphere(moonCenter, moonRadius, nullptr, moonMat));
		world.light.push_back(new PointLight(moonCenter, RGBColor(0.5f, 0.5f, 0.5f)));
		Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
		Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));

		Material* whiteMaterial = new LambertianMaterial(blacktex, whitetex);
		world.fog = new HomogeniousFog(TheMoon, 0.025, whiteMaterial);

//		DummyMaterial* moonMat = new DummyMaterial();
//		ConstantTexture* blueTex = new ConstantTexture(
//				RGBColor(0.02f, 0.02f, 0.96f));
//		ConstantTexture* blackTex = new ConstantTexture(
//				RGBColor(0.f, 0.f, 0.f));
//		ConstantTexture* redTex = new ConstantTexture(
//				RGBColor(0.96f, 0.02f, 0.02f));
//		Material* moonMat1 = new LambertianMaterial(blackTex, redTex);
//		Material* moonMat2 = new LambertianMaterial(blueTex, redTex);
//		ConstructiveSolidGeometry* csg1 = new ConstructiveSolidGeometry(
//				ConstructiveSolidGeometry::DIFFERENCE);
//		Point center1 = Point(4000.f, 4000.f, 20000.f);
//		Point center2 = Point(4100.f, 4060.f, 19700.f);
//		Vector vec = (center1 - center2);
//		csg1->add(new Sphere(center1, 700.f, nullptr, moonMat1));
//		csg1->add(new Sphere(center2, 700.f, nullptr, moonMat));
//		TheMoon->add(csg1);
//		Vector camTOmoon = (center1 - camPoint) / (center1.z - camPoint.z);
//		Point discCenter = camPoint + 50000.f * camTOmoon
//				+ Vector(-40.f, -40.f, 0);
//		TheMoon->add(
//				new Disc(discCenter, -camTOmoon.normalize(), 1800.f, nullptr,
//						moonMat1));
//		world.light.push_back(
//				new SpotLight(camPoint + 49500.f * camTOmoon,
//						discCenter - (camPoint + 49500.f * camTOmoon), pi,
//						0.25f, RGBColor::rep(253.f * 20000000.f / 255.f)));
//		Vector sLight = Vector(-1.f, -1.f, 0.f).normalize();
//		world.light.push_back(
//				new PointLight(
//						(center1 + sLight * 2000 + Vector(0.f, 0.f, 1000.f)),
//						RGBColor::rep(253.f * 5000000.f / 255.f)));
//		Vector sLight1 = Vector(0.f, -1.f, 0.f).normalize();
//		world.light.push_back(
//				new PointLight(
//						(center1 + sLight1 * 2000 + Vector(0.f, 0.f, 2000.f)),
//						RGBColor::rep(253.f * 12000000.f / 255.f)));
//		Vector sLight2 = Vector(-1.f, 0.f, 0.f).normalize();
//		world.light.push_back(
//				new PointLight(
//						(center1 + sLight2 * 2000 + Vector(0.f, 0.f, 0.f)),
//						RGBColor::rep(253.f * 2000000.f / 255.f)));
	}

	//The stars
	if(STARS)
	{
		StarTexture* starTex = new StarTexture();
		ConstantTexture* blackTex = new ConstantTexture(
				RGBColor(0.f, 0.f, 0.f));
		Material* stars = new LambertianMaterial(blackTex, starTex);
		TheStars->add(
				new InfinitePlane(Point(0.f, 0.f, 1000000.f),
						Vector(0.f, 0.f, -1.f), nullptr, stars));
	}

	//DEBUG LIGHT
	if(DEBUGLIGHT){
	world.light.push_back(
			new DirectionalLight(Vector(0.f, -1.f, 0.f),
					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
	world.light.push_back(
			new DirectionalLight(Vector(0.f, 1.f, 0.f),
					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
	world.light.push_back(
			new DirectionalLight(Vector(1.f, 0.f, 0.f),
					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
	world.light.push_back(
			new DirectionalLight(Vector(-1.f, 0.f, 0.f),
					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
	world.light.push_back(
			new DirectionalLight(Vector(0.f, 0.f, -1.f),
					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
	world.light.push_back(
			new DirectionalLight(Vector(0.f, 0.f, 1.f),
					RGBColor(253.f / 255.f, 253.f / 255.f, 253.f / 255.f)));
	}

	//The Tree(s)
//	{
//		loadOBJ(scene, "models/", "cow.obj");
//	}

	scene->add(TheSea);
	scene->add(TheSun);
	scene->add(TheLandscape);
	scene->add(TheMoon);
	scene->add(TheStars);
	world.scene = scene;
	RayMarchingIntegrator integrator(&world);
//	RayTracingIntegrator integrator(&world);
	Renderer engine(&cam, &integrator);
	engine.setSamples(1.f);
	engine.render(img);
	img.writePNG("rendComp.png");
}

#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>

#include <cmath>
#include <math.h>

#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/cameras/perspective.h>

#include <rt/groups/simplegroup.h>

#include <rt/integrators/raytrace.h>

#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>

#include <rt/solids/fracLand.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/sphere.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>

using namespace rt;

void a_rendComp(){
    Image img(800, 800);
    World world;
    SimpleGroup* scene = new SimpleGroup();

    PerspectiveCamera cam(Point(0.f, 20.f, -20.f), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

    ImageTexture* mirrorTex = new ImageTexture("models/17_DIFFUSE.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    FlatMaterial* mirror = new FlatMaterial(mirrorTex);

    ConstantTexture* lambTex = new ConstantTexture(RGBColor (253.f / 255.f, 184.f / 255.f, 19.f / 255.f));
    LambertianMaterial* lamb = new LambertianMaterial(lambTex, nullptr);

    ConstantTexture* seaTex = new ConstantTexture(RGBColor (19.f / 255.f, 19.f / 255.f, 224.f / 255.f));
    LambertianMaterial* sea = new LambertianMaterial(seaTex, nullptr);

    scene->add(new Sphere(Point(-400.f, 500.f, 2000.f), 100.f, nullptr, lamb));
    scene->add(new FracLand(Point(800.f, 0.f, 1000.f), Point(-800.f, 0.f, 1000.f), Point(0.f, 0.f, 0.f), 3, 20.f, nullptr, nullptr));
    scene->add(new InfinitePlane(Point(0.0f,0.0f,-0.018f), Vector(0.f, 1.f, 0.f), nullptr, sea));

    world.scene = scene;
    RayTracingIntegrator integrator(&world);
    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG("rendComp.png");
}

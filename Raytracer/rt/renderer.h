#ifndef CG1RAYTRACER_RENDERER_HEADER
#define CG1RAYTRACER_RENDERER_HEADER

#include <core/scalar.h>

namespace rt {

class Image;
class Camera;
class Integrator;

class Renderer {
public:
	Camera* camera;
	Integrator* integrator;

	uint sampleCount;

    Renderer(Camera* cam, Integrator* integrator);
    void setSamples(uint samples);
    void render(Image& img);
    void test_render1(Image& img);
    void test_render2(Image& img);

};

}

#endif

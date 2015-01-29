#ifndef CG1RAYTRACER_WORLD_HEADER
#define CG1RAYTRACER_WORLD_HEADER

#include <rt/primitive.h>
#include <rt/lights/ambient.h>
#include <rt/volume/fog.h>

namespace rt {
class Light;
class World {
public:
    Primitive* scene;
	typedef std::vector<Light*> LightVector;
    LightVector light;
    //AmbientLight* ambientLight = nullptr;
    Fog* fog = nullptr;

};
}

#endif

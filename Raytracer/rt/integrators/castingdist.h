#ifndef CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER
#define CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER

#include <rt/integrators/integrator.h>
#include <rt/world.h>
#include <core/color.h>

namespace rt {

class World;
class Ray;
class RGBColor;

class RayCastingDistIntegrator : public Integrator {
public:
	RGBColor nearColor;
	RGBColor farColor;
	float nearDistance;
	float farDistance;

    RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist);
    virtual RGBColor getRadiance(const Ray& ray) const;
};

}

#endif

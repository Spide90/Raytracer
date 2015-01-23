/*
 * volumeRaytrace.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#ifndef RT_INTEGRATORS_VOLUMERAYTRACE_H_
#define RT_INTEGRATORS_VOLUMERAYTRACE_H_


#include <rt/integrators/integrator.h>

namespace rt {
class World;
class Ray;
class RGBColor;

class VolumeRaytracingIntegrator : public Integrator {
public:
    VolumeRaytracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
};

}


#endif /* RT_INTEGRATORS_VOLUMERAYTRACE_H_ */

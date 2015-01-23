/*
 * rayMarching.h
 *
 *  Created on: 23.01.2015
 *      Author: chris
 */

#ifndef RT_INTEGRATORS_RAYMARCHING_H_
#define RT_INTEGRATORS_RAYMARCHING_H_

#include <rt/integrators/integrator.h>

namespace rt {
class World;
class Ray;
class RGBColor;

class RayMarchingIntegrator : public Integrator {
public:
    RayMarchingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;

    float noise(int x, int y, int z) {
    	int n = x + y * 57 + z * 997;
    	n = (n << 13) ^ n;
    	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }
};

}



#endif /* RT_INTEGRATORS_RAYMARCHING_H_ */

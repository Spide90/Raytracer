/*
 * castingdist.cpp
 *
 *  Created on: 06.11.2014
 *      Author: chris
 */

#include <rt/integrators/castingdist.h>
#include <core/color.h>
#include <rt/intersection.h>
#include <rt/ray.h>
#include <rt/world.h>
#include <core/color.h>
#include <rt/integrators/integrator.h>

#include <stdio.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist,
		const RGBColor& farColor, float farDist) :
		Integrator(world), nearColor(nearColor), farColor(farColor), nearDistance(nearDist), farDistance(farDist) {

}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		float cosine = fabs(dot(-intersection.ray.d, intersection.normalVector));
		float interpolation = (intersection.distance - nearDistance) / (farDistance - nearDistance);
		RGBColor color =  ((1 - interpolation) * nearColor + (interpolation) * farColor) * cosine;
		return color;
	} else {
		return RGBColor(0, 0, 0);
	}
}

}


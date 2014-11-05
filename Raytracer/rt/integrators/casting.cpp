/*
 * casting.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/integrators/casting.h>
#include <rt/integrators/integrator.h>
#include <core/color.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <core/vector.h>
#include <math.h>
#include <rt/bbox.h>

#include <stdio.h>

namespace rt {


RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		float greyScale = fabs(dot(intersection.ray.d, intersection.normalVector));
		return RGBColor(greyScale, greyScale, greyScale);
	} else {
		return RGBColor(0, 0, 0);
	}
}

}


/*
 * raytrace.cpp
 *
 *  Created on: 18.11.2014
 *      Author: chris
 */

#include <rt/integrators/raytrace.h>
#include <rt/integrators/integrator.h>
#include <core/color.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/lights/light.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		RGBColor color;
		for (int i = 0; i < world->light.size(); i++) {
			LightHit shadowRay = world->light[i]->getLightHit(intersection.local());
			if (fabs(dot(intersection.normalVector, shadowRay.direction)) < pi/2) {
				Ray shadow = Ray(intersection.local(), shadowRay.direction);
				Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
				if (!shadowRayIntersection) {
					color = color + world->light[i]->getIntensity(shadowRay);
				} else {
					//obstacle between light source and hitpoint
				}
			} else {
				//wrong side
			}
		}

		return color;
	} else {
		return RGBColor(0, 0, 0);
	}
}

}


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
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

#define EPSILON 0.00001

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		RGBColor color = RGBColor(0, 0, 0);
		Point local;
		if (intersection.solid->texMapper == nullptr) {
			local = WorldMapper(Float4::rep(1)).getCoords(intersection);
		} else {
			local = intersection.solid->texMapper->getCoords(intersection);
		}
		RGBColor emission;
		if(intersection.solid->material == nullptr){
			float greyScale = fabs(dot(intersection.ray.d, intersection.normalVector));
			emission = RGBColor(greyScale, greyScale, greyScale);
		}
		else{
			emission = intersection.solid->material->getEmission(local, intersection.normalVector, -ray.d);
		}
		for (int i = 0; i < world->light.size(); i++) {
			LightHit shadowRay = world->light[i]->getLightHit(intersection.hitPoint());
			if (dot(intersection.normalVector, shadowRay.direction) > 0) {
				Ray shadow = Ray(intersection.hitPoint() + EPSILON * shadowRay.direction, shadowRay.direction);
				Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
				if (!shadowRayIntersection) {
					RGBColor reflectance = intersection.solid->material->getReflectance(local,
							intersection.normalVector, -ray.d, shadowRay.direction);
					RGBColor intensity = world->light[i]->getIntensity(shadowRay);
					RGBColor lightSourceColor = (reflectance * intensity);
					color = color + lightSourceColor;
				}
			}
		}
		return (color + emission);
	} else {
		return RGBColor(0, 0, 0);
	}
}

}


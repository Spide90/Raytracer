/*
 * volumeRaytrace.cpp
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include <rt/integrators/volumeRaytrace.h>
#include <rt/integrators/integrator.h>
#include <core/color.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

#define EPSILON 0.000001

RGBColor VolumeRaytracingIntegrator::getRadiance(const Ray& ray) const {
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
		if (intersection.solid->material == nullptr) {
			float greyScale = fabs(dot(intersection.ray.d, intersection.normalVector));
			emission = RGBColor(greyScale, greyScale, greyScale);
		} else {
			emission = intersection.solid->material->getEmission(local, intersection.normalVector, -ray.d);
		}
		for (int i = 0; i < world->light.size(); i++) {
			LightHit shadowRay = world->light[i]->getLightHit(intersection.hitPoint());
			if (dot(intersection.normalVector, shadowRay.direction) > 0) {
				Ray shadow = Ray(intersection.hitPoint() + EPSILON * shadowRay.direction, shadowRay.direction);
				Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
				if (!shadowRayIntersection) {
					RGBColor reflectance;
					if (intersection.solid->material == nullptr) {
						reflectance = RGBColor(0.5, 0.5, 0.5);
					} else {
						reflectance = intersection.solid->material->getReflectance(local,
								intersection.normalVector, -ray.d, shadowRay.direction);
					}
					RGBColor intensity = world->light[i]->getIntensity(shadowRay);
					RGBColor lightSourceColor = (reflectance * intensity); // * transmittance
					//+(1 - transmittance) * fog;
					color = (color + lightSourceColor);
				}
			}
		}
		RGBColor fog = world->fog->getColor(intersection.hitPoint(), intersection.normal(), Vector(0, 0, 0), Vector(0, 0, 0));
		float transmittance = world->fog->transmittance(ray.o, intersection.hitPoint());
		return (color + emission) * transmittance + (1 - transmittance) * fog;;
	} else {
		RGBColor fog = world->fog->getColor(intersection.hitPoint(), intersection.normal(), Vector(0, 0, 0), Vector(0, 0, 0));
		return fog;
	}
}

}


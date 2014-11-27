/*
 * reraytrace.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/integrators/recraytrace.h>
#include <rt/integrators/integrator.h>
#include <core/color.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/materials/material.h>


namespace rt {


#define EPSILON 0.00001

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		RGBColor color = RGBColor(0, 0, 0);
		Material::SampleReflectance sample;
		Ray sampleRay;
		switch (intersection.solid->material->useSampling()) {
		case Material::SAMPLING_NOT_NEEDED:
			for (int i = 0; i < world->light.size(); i++) {
				LightHit shadowRay = world->light[i]->getLightHit(intersection.local());
				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
					Ray shadow = Ray(intersection.local() + EPSILON * shadowRay.direction, shadowRay.direction);
					Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
					if (!shadowRayIntersection) {
						RGBColor reflectance = intersection.solid->material->getReflectance(intersection.local(),
								intersection.normalVector, -ray.d, shadowRay.direction);
						RGBColor emission = intersection.solid->material->getEmission(intersection.local(),
														intersection.normalVector, -ray.d);
						RGBColor intensity = world->light[i]->getIntensity(shadowRay);
						RGBColor lightSourceColor = (reflectance * intensity);
						color = color + lightSourceColor + emission;
					}
				}
			}
			break;
		case Material::SAMPLING_ALL:
			sample = intersection.solid->material->getSampleReflectance(intersection.local(), intersection.normalVector, -intersection.ray.d);
			sampleRay = Ray(intersection.local(), sample.direction);
			color = color + sample.reflectance + getRadiance(sampleRay);
			break;
		case Material::SAMPLING_SECONDARY:
			LOG_DEBUG("not yet implemented")
			break;
		default:
			break;
		}

		return color;
	} else {
		return RGBColor(0, 0, 0);
	}
}

}


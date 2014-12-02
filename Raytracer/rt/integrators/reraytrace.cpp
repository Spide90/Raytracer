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

#define EPSILON 0.000001
#define MAX_RECURSION_DEPTH 6

int recursionDepth = 0;

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		RGBColor color = RGBColor(0, 0, 0);
		RGBColor emission = intersection.solid->material->getEmission(intersection.local(), intersection.normalVector, -ray.d);
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
						RGBColor intensity = world->light[i]->getIntensity(shadowRay);
						RGBColor lightSourceColor = (reflectance * intensity);
						color = color + lightSourceColor;
					}
				}
			}
			break;
		case Material::SAMPLING_ALL:
			sample = intersection.solid->material->getSampleReflectance(intersection.local(), intersection.normalVector,
					-intersection.ray.d);
			sampleRay = Ray(intersection.local() + EPSILON * sample.direction, sample.direction);
			if (recursionDepth > MAX_RECURSION_DEPTH) {
				recursionDepth = 0;
			} else {
				recursionDepth++;
				color = color + getRadiance(sampleRay) * sample.reflectance;
			}

			break;
		case Material::SAMPLING_SECONDARY:
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
						color = color + lightSourceColor;
					}
				}
			}
			sample = intersection.solid->material->getSampleReflectance(intersection.local(), intersection.normalVector,
					-intersection.ray.d);
			if (sample.direction != Vector(0, 0, 1) && sample.reflectance != RGBColor(0.f, 0.f, 0.f)) {
				sampleRay = Ray(intersection.local() + EPSILON * sample.direction, sample.direction);
				if (recursionDepth > MAX_RECURSION_DEPTH) {
					recursionDepth = 0;
				} else {
					recursionDepth++;
					color = color + getRadiance(sampleRay) * sample.reflectance;
				}
			}
			break;
		default:
			break;
		}
		recursionDepth = 0;
		return color + emission;
	} else {
		return RGBColor(0, 0, 0);
	}
}

}


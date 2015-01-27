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
#define MAX_RECURSION_DEPTH 15

int VolRecursionDepth = 0;

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
			float greyScale = fabs(
					dot(intersection.ray.d, intersection.normalVector));
			emission = RGBColor(greyScale, greyScale, greyScale);
		} else {
			emission = intersection.solid->material->getEmission(
					intersection.point, intersection.normalVector, -ray.d);
//			emission = intersection.solid->material->getEmission(local, intersection.normalVector, -ray.d);
		}
		Material::SampleReflectance sample;
		Ray sampleRay;
		switch (intersection.solid->material->useSampling()) {
		case Material::SAMPLING_NOT_NEEDED:
			for (int i = 0; i < world->light.size(); i++) {
				LightHit shadowRay = world->light[i]->getLightHit(
						intersection.hitPoint());
				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
					Ray shadow = Ray(
							intersection.hitPoint()
									+ EPSILON * intersection.normal(),
							shadowRay.direction);
					//TODO more epsilon?
					Intersection shadowRayIntersection =
							world->scene->intersect(shadow,
									shadowRay.distance - 2 * EPSILON);
					if (!shadowRayIntersection) {
						RGBColor reflectance;
						if (intersection.solid->material == nullptr) {
							reflectance = RGBColor(0.5, 0.5, 0.5);
						} else {
							reflectance =
									intersection.solid->material->getReflectance(
											intersection.point,
											intersection.normalVector, -ray.d,
											shadowRay.direction);
//							reflectance = intersection.solid->material->getReflectance(local,
//																intersection.normalVector, -ray.d, shadowRay.direction);
						}
						RGBColor intensity = world->light[i]->getIntensity(
								shadowRay);
						RGBColor lightSourceColor = (reflectance * intensity);
						color = color + lightSourceColor;
					}
				}
			}
			break;

		case Material::SAMPLING_ALL:
			sample = intersection.solid->material->getSampleReflectance(
					intersection.hitPoint(), intersection.normalVector,
					-intersection.ray.d);
//			sample = intersection.solid->material->getSampleReflectance(local, intersection.normalVector,
//					-intersection.ray.d);
			sampleRay = Ray(
					intersection.hitPoint() + EPSILON * sample.direction,
					sample.direction);
			if (VolRecursionDepth > MAX_RECURSION_DEPTH) {
				VolRecursionDepth = 0.f;
			} else {
				VolRecursionDepth++;
				color = color + getRadiance(sampleRay) * sample.reflectance;
			}
			break;

		case Material::SAMPLING_SECONDARY:
			for (int i = 0; i < world->light.size(); i++) {
				LightHit shadowRay = world->light[i]->getLightHit(
						intersection.hitPoint());
				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
					Ray shadow = Ray(
							intersection.hitPoint()
									+ EPSILON * intersection.normal(),
							shadowRay.direction);
					Intersection shadowRayIntersection =
							world->scene->intersect(shadow, shadowRay.distance);
					if (!shadowRayIntersection) {
						RGBColor reflectance =
								intersection.solid->material->getReflectance(
										intersection.hitPoint(),
										intersection.normalVector, -ray.d,
										shadowRay.direction);
						RGBColor emission =
								intersection.solid->material->getEmission(local,
										intersection.normalVector, -ray.d);
						RGBColor intensity = world->light[i]->getIntensity(
								shadowRay);
						RGBColor lightSourceColor = (reflectance * intensity);
						color = color + lightSourceColor;
					}
				}
			}
			sample = intersection.solid->material->getSampleReflectance(local,
					intersection.normalVector, -intersection.ray.d);
			if (sample.direction != Vector(0, 0, 1)
					&& sample.reflectance != RGBColor(0.f, 0.f, 0.f)) {
				sampleRay = Ray(
						intersection.hitPoint() + EPSILON * sample.direction,
						sample.direction);
				if (VolRecursionDepth > MAX_RECURSION_DEPTH) {
					VolRecursionDepth = 0;
				} else {
					VolRecursionDepth++;
					color = color + getRadiance(sampleRay) * sample.reflectance;
				}
			}
			break;
		default:
			break;
		}
		VolRecursionDepth = 0;
		if (world->fog->getPrimtive()->intersect(ray)) {
			RGBColor fog = world->fog->getColor(intersection.hitPoint(),
					intersection.normal(), Vector(0, 0, 0), Vector(0, 0, 0));
			float transmittance = world->fog->transmittance(ray.o,
					intersection.hitPoint());
			return (color + emission) * transmittance
					+ (1 - transmittance) * fog;;
		} else{
			return color + emission;
		}
	} else {
		RGBColor fog = world->fog->getColor(intersection.hitPoint(),
				intersection.normal(), Vector(0, 0, 0), Vector(0, 0, 0));
		return fog;
	}
}

}

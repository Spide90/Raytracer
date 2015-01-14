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

#define EPSILON 0.005
#define MAX_RECURSION_DEPTH 6

int recursionDepth = 0;

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
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
			emission = intersection.solid->material->getEmission(intersection.point, intersection.normalVector, -ray.d);
//			emission = intersection.solid->material->getEmission(local, intersection.normalVector, -ray.d);
		}
		Material::SampleReflectance sample;
		Ray sampleRay;
		switch (intersection.solid->material->useSampling()) {
		case Material::SAMPLING_NOT_NEEDED:
			for (int i = 0; i < world->light.size(); i++) {
				LightHit shadowRay = world->light[i]->getLightHit(intersection.hitPoint());
				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
					Ray shadow = Ray(intersection.hitPoint() + EPSILON * intersection.normal(), shadowRay.direction);
					//TODO more epsilon?
					Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance - 2 * EPSILON);
					if (!shadowRayIntersection) {
						RGBColor reflectance;
						if (intersection.solid->material == nullptr) {
							reflectance = RGBColor(0.5, 0.5, 0.5);
						} else {
							reflectance = intersection.solid->material->getReflectance(intersection.point,
									intersection.normalVector, -ray.d, shadowRay.direction);
//							reflectance = intersection.solid->material->getReflectance(local,
//																intersection.normalVector, -ray.d, shadowRay.direction);
						}
						RGBColor intensity = world->light[i]->getIntensity(shadowRay);
						RGBColor lightSourceColor = (reflectance * intensity);
						color = color + lightSourceColor;
					}
				}
			}
			break;

		case Material::SAMPLING_ALL:
//			for (int i = 0; i < world->light.size(); i++) {
//				LightHit shadowRay = world->light[i]->getLightHit(intersection.hitPoint());
//				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
//					Ray shadow = Ray(intersection.hitPoint() + EPSILON * intersection.normal(), shadowRay.direction);
//					//TODO more epsilon?
//					Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance - 2 * EPSILON);
//					if (!shadowRayIntersection) {
//						RGBColor reflectance;
//						if (intersection.solid->material == nullptr) {
//							sample.reflectance = RGBColor(0.5, 0.5, 0.5);
//						} else {
//							sample = intersection.solid->material->getSampleReflectance(intersection.hitPoint(), intersection.normalVector,
//									-intersection.ray.d);
//							sampleRay = Ray(intersection.hitPoint() + EPSILON * sample.direction, sample.direction);
//						}
//						RGBColor intensity = world->light[i]->getIntensity(shadowRay);
//						RGBColor lightSourceColor = (sample.reflectance * intensity);
//						if(recursionDepth > MAX_RECURSION_DEPTH){
//							recursionDepth = 0.f;
//						}
//						else{
//							recursionDepth++;
//							color = color + lightSourceColor * getRadiance(sampleRay);
//						}
//					}
//				}
//			}

			sample = intersection.solid->material->getSampleReflectance(intersection.hitPoint(), intersection.normalVector,
					-intersection.ray.d);
			sampleRay = Ray(intersection.hitPoint() + EPSILON * sample.direction, sample.direction);
			if (recursionDepth > MAX_RECURSION_DEPTH) {
				recursionDepth = 0.f;
			} else {
				recursionDepth++;
				color = color + getRadiance(sampleRay) * sample.reflectance;
			}
			break;

		case Material::SAMPLING_SECONDARY:
			for (int i = 0; i < world->light.size(); i++) {
				LightHit shadowRay = world->light[i]->getLightHit(intersection.hitPoint());
				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
					Ray shadow = Ray(intersection.hitPoint() + EPSILON * intersection.normal(), shadowRay.direction);
					Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
					if (!shadowRayIntersection) {
						RGBColor reflectance = intersection.solid->material->getReflectance(
								intersection.hitPoint(), intersection.normalVector, -ray.d, shadowRay.direction);
						RGBColor emission = intersection.solid->material->getEmission(local,
								intersection.normalVector, -ray.d);
						RGBColor intensity = world->light[i]->getIntensity(shadowRay);
						RGBColor lightSourceColor = (reflectance * intensity);
						color = color + lightSourceColor;
					}
				}
			}
			sample = intersection.solid->material->getSampleReflectance(local,
					intersection.normalVector, -intersection.ray.d);
			if (sample.direction != Vector(0, 0, 1) && sample.reflectance != RGBColor(0.f, 0.f, 0.f)) {
				sampleRay = Ray(intersection.hitPoint() + EPSILON * sample.direction, sample.direction);
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


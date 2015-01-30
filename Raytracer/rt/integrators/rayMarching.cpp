/*
 * rayMarching.cpp
 *
 *  Created on: 23.01.2015
 *      Author: chris
 */

#include <rt/integrators/rayMarching.h>
#include <rt/integrators/integrator.h>
#include <core/color.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

#include <rt/materials/combine.h>
#include <rt/materials/dummy.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <rt/materials/mirror.h>
#include <rt/materials/phong.h>
#include <rt/textures/constant.h>

#include <rt/textures/imagetex.h>
#include <rt/materials/flatmaterial.h>
#include <rt/textures/perlin.h>

namespace rt {

#define EPSILON 0.0001
#define STEP_SIZE 2.f
#define MAX_RECURSION_DEPTH 15

int MarchRecursionDepth = 0;

RGBColor RayMarchingIntegrator::getRadiance(const Ray& ray) const {
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
		Material::SampleReflectance sample;
		Ray sampleRay;
		switch (intersection.solid->material->useSampling()) {
		case Material::SAMPLING_NOT_NEEDED:
			for (int i = 0; i < world->light.size(); i++) {
				LightHit shadowRay = world->light[i]->getLightHit(intersection.hitPoint());
				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
					Ray shadow = Ray(intersection.hitPoint() + EPSILON * shadowRay.direction, shadowRay.direction);
					//TODO more epsilon?
					Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
					if (!shadowRayIntersection) {
						RGBColor reflectance;
						if (intersection.solid->material == nullptr) {
							reflectance = RGBColor(0.5, 0.5, 0.5);
						} else {
							reflectance = intersection.solid->material->getReflectance(local,
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
			sample = intersection.solid->material->getSampleReflectance(intersection.hitPoint(),
					intersection.normalVector, -intersection.ray.d);
			//			sample = intersection.solid->material->getSampleReflectance(local, intersection.normalVector,
			//					-intersection.ray.d);
			sampleRay = Ray(intersection.hitPoint() + EPSILON * sample.direction, sample.direction);
			if (MarchRecursionDepth > MAX_RECURSION_DEPTH) {
				MarchRecursionDepth = 0.f;
			} else {
				MarchRecursionDepth++;
				color = color + getRadiance(sampleRay) * sample.reflectance;
			}
			break;

		case Material::SAMPLING_SECONDARY:
			for (int i = 0; i < world->light.size(); i++) {
				LightHit shadowRay = world->light[i]->getLightHit(intersection.hitPoint());
				if (dot(intersection.normalVector, shadowRay.direction) > 0) {
					Ray shadow = Ray(intersection.hitPoint() + EPSILON * intersection.normal(),
							shadowRay.direction);
					Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
					if (!shadowRayIntersection) {
						RGBColor reflectance = intersection.solid->material->getReflectance(local,
								intersection.normalVector, -ray.d, shadowRay.direction);
						RGBColor emission = intersection.solid->material->getEmission(local,
								intersection.normalVector, -ray.d);
						RGBColor intensity = world->light[i]->getIntensity(shadowRay);
						RGBColor lightSourceColor = (reflectance * intensity);
						color = color + lightSourceColor;
					}
				}
			}
			sample = intersection.solid->material->getSampleReflectance(local, intersection.normalVector,
					-intersection.ray.d);
			if (sample.direction != Vector(0, 0, 1) && sample.reflectance != RGBColor(0.f, 0.f, 0.f)) {
				sampleRay = Ray(intersection.hitPoint() + EPSILON * sample.direction, sample.direction);
				if (MarchRecursionDepth > MAX_RECURSION_DEPTH) {
					MarchRecursionDepth = 0;
				} else {
					MarchRecursionDepth++;
					color = color + getRadiance(sampleRay) * sample.reflectance;
				}
			}
			break;
		default:
			break;
		}
		MarchRecursionDepth = 0;

		if (!world->fog) {
			return color + emission;
		}
		/*
		 RGBColor fog = world->fog->modulateColor(ray.o, intersection.hitPoint());
		 float transmittance = world->fog->transmittance(ray.o, intersection.hitPoint());
		 return (color + emission) * transmittance + (1 - transmittance) * fog;*/
		Intersection i1 = world->fog->getPrimitive()->intersect(ray, intersection.distance);
		if (i1) {
			RGBColor fogColor = RGBColor::rep(0);
			float transmittance = 1;
			float enterDistance = 0;			//i1.distance;
			//float exitDistance = i1.exitDistance == i1.distance ? intersection.distance : i1.exitDistance;
			float exitDistance = intersection.distance;			//std::min(i1.exitDistance, intersection.distance);
			while (enterDistance < exitDistance) {
				float stepSize = std::min(STEP_SIZE, exitDistance - enterDistance);
				Point deltaPoint = ray.o + (enterDistance + stepSize / 2) * ray.d;
				float deltaTransmittance = exp(-world->fog->getDensity(deltaPoint) * stepSize);
				RGBColor deltaColor = RGBColor(0, 0, 0);
				for (int i = 0; i < world->light.size(); i++) {
					LightHit shadowRay = world->light[i]->getLightHit(deltaPoint);
					Ray shadow = Ray(deltaPoint + EPSILON * shadowRay.direction, shadowRay.direction);
					Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
					if (!shadowRayIntersection) {
						RGBColor intensity = world->light[i]->getIntensity(shadowRay);
						RGBColor lightSourceColor = (intensity);
						deltaColor = (deltaColor + lightSourceColor);
					}
				}
				fogColor = fogColor
						+ transmittance * (1 - deltaTransmittance) * deltaColor * world->fog->getColor(deltaPoint);
				transmittance *= deltaTransmittance;
				enterDistance += STEP_SIZE;
			}
			//LOG_DEBUG("fogcolor " << fogColor.r << ", " << fogColor.g << ", " << fogColor.b);
			return (color + emission) + fogColor;
		} else {
			return (color + emission);
		}
	} else {
		//if (!world->fog)
		return RGBColor(0, 0, 0);

		/*Intersection i1 = world->fog->getPrimitive()->intersect(ray);
		 if (i1) {
		 RGBColor fogColor = RGBColor::rep(0);
		 float transmittance = 1;
		 float enterDistance = i1.distance;
		 //float exitDistance = i1.exitDistance == i1.distance ? intersection.distance : i1.exitDistance;
		 float exitDistance = std::min(i1.exitDistance, intersection.distance);
		 while (enterDistance < exitDistance) {
		 float stepSize = std::min(STEP_SIZE, exitDistance - enterDistance);
		 Point deltaPoint = ray.o + (enterDistance + stepSize / 2) * ray.d;
		 float deltaTransmittance = exp(-world->fog->getDensity(deltaPoint) * stepSize);
		 RGBColor deltaColor = RGBColor(0, 0, 0);
		 for (int i = 0; i < world->light.size(); i++) {
		 LightHit shadowRay = world->light[i]->getLightHit(deltaPoint);
		 if (dot(intersection.normalVector, shadowRay.direction) > 0) {
		 Ray shadow = Ray(deltaPoint + EPSILON * shadowRay.direction, shadowRay.direction);
		 Intersection shadowRayIntersection = world->scene->intersect(shadow, shadowRay.distance);
		 if (!shadowRayIntersection) {
		 RGBColor reflectance = world->fog->getColor(deltaPoint);
		 RGBColor intensity = world->light[i]->getIntensity(shadowRay);
		 RGBColor lightSourceColor = (reflectance * intensity);
		 deltaColor = (deltaColor + lightSourceColor);
		 }
		 }
		 }
		 fogColor = fogColor + transmittance * (1 - deltaTransmittance) * deltaColor;
		 transmittance *= deltaTransmittance;
		 enterDistance += STEP_SIZE;
		 }
		 return fogColor;
		 }
		 RGBColor fog = world->fog->getColor(intersection.hitPoint());*/
		//return fog;
	}
}

}


/*
 * motionblur.cpp
 *
 *  Created on: 09.01.2015
 *      Author: chris
 */

#include <rt/materials/motionblur.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/point.h>

#include <core/random.h>
#include <math.h>

namespace rt {

MotionBlurMaterial::MotionBlurMaterial(Texture* emission, Texture* diffuse, Vector movementDirection) :
		emission(emission), diffuse(diffuse), movementDirection(movementDirection) {
}

RGBColor MotionBlurMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	float rnd = random();
	Point blurredTexPoint = texPoint + rnd * movementDirection;
	return diffuse->getColor(blurredTexPoint) * dot(inDir.normalize(), normal) / M_PI;
}

RGBColor MotionBlurMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	float rnd = random(2) - 1;
	Point blurredTexPoint = texPoint + rnd * movementDirection;
	return emission->getColor(blurredTexPoint);
}

Material::SampleReflectance MotionBlurMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return Material::SampleReflectance();
}

Material::Sampling MotionBlurMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}


/*
 * lambertian.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/vector.h>
#include <math.h>

namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse):emission(emission), diffuse(diffuse) {

}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	return diffuse->getColor(texPoint) * fabs(dot(inDir.normalize(), normal)) / M_PI;
}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return emission->getColor(texPoint);
}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return Material::SampleReflectance(normal, RGBColor(0,0,0));
}

Material::Sampling LambertianMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}


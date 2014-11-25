/*
 * lambertian.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse) {

}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {

}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {

}

Material::Sampling LambertianMaterial::useSampling() const {

}

}


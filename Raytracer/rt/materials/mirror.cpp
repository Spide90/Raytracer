/*
 * mirror.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/mirror.h>
#include <rt/materials/material.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa) {

}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {

}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}

Material::Sampling MirrorMaterial::useSampling() const {

}

}


/*
 * combine.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/combine.h>
#include <rt/materials/material.h>
#include <rt/materials/combine.h>
#include <vector>

namespace rt {

CombineMaterial::CombineMaterial() {

}

void CombineMaterial::add(Material* material, float weight) {

}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {

}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {

}

Material::Sampling CombineMaterial::useSampling() const {

}

}


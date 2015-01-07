/*
 * fuzzymirror.cpp
 *
 *  Created on: 07.01.2015
 *      Author: chris
 */

#include <rt/materials/fuzzymirror.h>
#include <rt/materials/material.h>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa,
		float fuzzyangle) : eta(eta), kappa(kappa), fuzzyAngle(fuzzyangle) {
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir, const Vector& inDir) const {

}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {

}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint,
		const Vector& normal, const Vector& outDir) const {

}

}


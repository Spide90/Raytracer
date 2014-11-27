/*
 * mirror.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/mirror.h>
#include <rt/materials/material.h>
#include <core/vector.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa):eta(eta), kappa(kappa) {

}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	float e2_k2 = eta*eta+kappa*kappa;
	float cosine = dot(inDir, normal);
	float cosine_2 = cosine*cosine;
	float r_par_2 = ((e2_k2)-cosine_2 - 2*eta*cosine + 1) / ((e2_k2)*cosine_2 + 2*eta*cosine + 1);
	float r_per_2 = ((e2_k2) - 2*eta*cosine + cosine_2) / ((e2_k2) + 2*eta*cosine + cosine_2);

	return RGBColor(0.5*(r_par_2+r_per_2), 0.5*(r_par_2+r_per_2), 0.5*(r_par_2+r_per_2));
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor(0,0,0);
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	Vector dir = 2*dot(outDir,normal)*normal - outDir;
	return Material::SampleReflectance(dir, this->getReflectance(texPoint, normal, outDir, dir));
}

Material::Sampling MirrorMaterial::useSampling() const {
	return SAMPLING_ALL;
}

}


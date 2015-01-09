/*
 * fuzzymirror.cpp
 *
 *  Created on: 07.01.2015
 *      Author: chris
 */

#include <rt/materials/fuzzymirror.h>
#include <rt/materials/material.h>
#include <core/random.h>
#include <core/matrix.h>
#include <core/point.h>
#include <core/float4.h>
#include <math.h>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa,
		float fuzzyangle) :
		eta(eta), kappa(kappa), fuzzyAngle(fuzzyangle) {
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint,
		const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	float e2_k2 = (eta * eta) + (kappa * kappa);
	float cosine = fabs(dot(inDir, normal));
	float cosine_2 = cosine * cosine;
	float r_par_2 = (e2_k2 * cosine_2 - 2 * eta * cosine + 1)
			/ (e2_k2 * cosine_2 + 2 * eta * cosine + 1);
	float r_per_2 = (e2_k2 - 2 * eta * cosine + cosine_2)
			/ (e2_k2 + 2 * eta * cosine + cosine_2);

	return 0.5
			* RGBColor(r_par_2 + r_per_2, r_par_2 + r_per_2, r_par_2 + r_per_2);
}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint,
		const Vector& normal, const Vector& outDir) const {
	return RGBColor(0, 0, 0);
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(
		const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	Vector dir = (2 * dot(outDir, normal) * normal - outDir);
	Vector ndir;

	do{
	float r1 = sqrt(random()) * tanf(fuzzyAngle);
	float r2 = random() * M_PI * 2;

	float x = r1 * cosf(r2);
	float y = r1 * sinf(r2);

	Point center = texPoint + dir.normalize();

	Vector span1 = cross(dir, normal).normalize();
	Vector span2 = cross(dir, span1).normalize();

	Point npoint = center + span1 * x + span2 * y;
	ndir = (npoint - texPoint).normalize();
	}while(dot(ndir, normal) <= 0);

	return Material::SampleReflectance(ndir,
			this->getReflectance(texPoint, normal, outDir, ndir));
}

}


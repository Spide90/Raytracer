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
	float cosine = dot(inDir, normal);
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
	Vector dir = (2 * dot(outDir, normal) * normal - outDir).normalize();

	float r1 = random(fuzzyAngle);
	float r2 = random(sqrt(fuzzyAngle));

	Point center = texPoint + dir;

	Vector span1 = cross(outDir, normal).normalize();
	Vector span2 = cross(outDir, span1).normalize();

	Point npoint = center + span1 * fuzzyAngle + span2 * sqrt(fuzzyAngle);
	Vector ndir = npoint - texPoint;

//	Vector axis = dir;
//
//	Matrix scaleMatrix(Float4(cosf(angle), 0, 0, 0), Float4(0, cosf(angle), 0, 0),
//			Float4(0, 0, cosf(angle), 0), Float4(0, 0, 0, 1));
//	Matrix rot1(Float4(0, -axis.z * sinf(angle), axis.y * sinf(angle), 0),
//			Float4(axis.z * sinf(angle), 0, -axis.x * sinf(angle), 0),
//			Float4(-axis.y * sinf(angle), axis.x * sinf(angle), 0, 0),
//			Float4(0, 0, 0, 0));
//	Matrix rot2(
//			Float4(axis.x * axis.x * (1 - cosf(angle)),
//					axis.x * axis.y * (1 - cosf(angle)),
//					axis.x * axis.z * (1 - cosf(angle)), 0),
//			Float4(axis.x * axis.y * (1 - cosf(angle)),
//					axis.y * axis.y * (1 - cosf(angle)),
//					axis.z * axis.y * (1 - cosf(angle)), 0),
//			Float4(axis.x * axis.z * (1 - cosf(angle)),
//					axis.y * axis.z * (1 - cosf(angle)),
//					axis.z * axis.z * (1 - cosf(angle)), 0),
//			Float4(0, 0, 0, 0));
//	rot2 = rot2 * (1/(axis.length()*axis.length()));
//	rot1 = rot1 * (1/axis.length());
//	Matrix rot = scaleMatrix + (rot1 + rot2);

	return Material::SampleReflectance(dir,
			this->getReflectance(texPoint, normal, outDir, ndir));
}

}


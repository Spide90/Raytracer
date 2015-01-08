/*
 * glass.cpp
 *
 *  Created on: 07.01.2015
 *      Author: chris
 */

#include <rt/materials/glass.h>
#include <rt/materials/material.h>
#include <math.h>
#include <core/random.h>

namespace rt {

GlassMaterial::GlassMaterial(float eta) :
		eta(eta) {
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint,
		const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	float cosI = -dot(inDir, normal);
	float sinI2 = eta * eta * (1 - cosI * cosI);
	float cosT = sqrt(1 - sinI2);

	float ueta = eta;

	float r_Orth = (cosI - ueta * cosT) / (cosI + ueta * cosT);
	float r_Par = (ueta * cosI - cosT) / (ueta * cosI + cosT);

	float ret = (r_Orth * r_Orth + r_Par * r_Par) * 0.5;

	return RGBColor(ret, ret, ret);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return RGBColor(0, 0, 0);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(
		const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	float blubb = random();

	if (blubb >= 0.5) {
		Vector dir = (2 * dot(outDir, normal) * normal - outDir).normalize();
		return Material::SampleReflectance(dir,
				this->getReflectance(texPoint, normal, outDir, dir));
	} else {
		float angle = acosf(dot(outDir, normal));
		float ueta = eta;
		if (angle > M_PI / 2) {
			ueta = 1 / ueta;
		}

		float cos_phi_i = dot(outDir, normal);
		float sin_phi_t_2 = ueta * ueta
				* (1 - cos_phi_i * cos_phi_i);
		Vector dir = ueta * outDir
				+ (ueta * cos_phi_i - sqrt(1 - sin_phi_t_2)) * normal;
		return Material::SampleReflectance(dir,
				this->getReflectance(texPoint, normal, outDir, dir));
	}
}

}


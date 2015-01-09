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
	float cosI = dot(inDir, normal);
	float ueta = eta;
	Vector unormal = normal;
	float n1 = 1.f;
	float n2 = 1.f / ueta;

	if(cosI < 0){
		LOG_DEBUG("test");
		unormal = -unormal;
		cosI = dot(outDir, unormal);
		n1 = 1 / ueta;
		n2 = 1.f;
		ueta = 1 / eta;
	}

	float sinI2 = ueta * ueta * (1 - cosI * cosI);

	if(sinI2 > 1.f){
		return RGBColor(1.f, 1.f, 1.f);
	}

	float cosT = sqrtf(1 - sinI2);

	float r_Orth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
	float r_Par = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);

	float ret = (r_Orth * r_Orth + r_Par * r_Par) * 0.5;

	return RGBColor(ret, ret, ret);

//	return RGBColor(1.f, 1.f, 1.f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return RGBColor(0, 0, 0);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(
		const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	Vector unormal = normal;
	Vector dir;
	float ueta = eta;
	float n1 = 1.f;
	float n2 = 1.f / ueta;

	float cosI = dot(outDir, unormal);

	if(cosI < 0){
		unormal = -unormal;
		cosI = dot(outDir, unormal);
		n1 = 1 / ueta;
		n2 = 1.f;
		ueta = 1 / eta;
	}

	float sinI2 = ueta * ueta * (1 - cosI * cosI);

	if (sinI2 > 1.f) {
		Vector ndir = (2 * dot(outDir, unormal) * unormal - outDir).normalize();
		return Material::SampleReflectance(ndir, RGBColor(1.f, 1.f, 1.f));
	}

	float cosT = sqrtf(1 - sinI2);
//
//	float r_Orth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
//	float r_Par = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
//
//	float ret = (r_Orth * r_Orth + r_Par * r_Par) * 0.5;

	float blubb = random();

	if (blubb < 0.5) {
		dir = (2 * dot(outDir, unormal) * unormal - outDir).normalize();
//		return Material::SampleReflectance(dir,
//				2.f * RGBColor(ret, ret, ret));
		return Material::SampleReflectance(dir,
						2.f * (this->getReflectance(texPoint, unormal, outDir, dir)));
	} else {
		dir = (-ueta * outDir
				+ (ueta * cosI - cosT) * unormal).normalize();
//		ret = 1 - ret;
		return Material::SampleReflectance(dir,
				2.f * (this->getReflectance(texPoint, unormal, outDir, dir)));
	}
//	return Material::SampleReflectance(dir,
//			2.f * RGBColor(ret, ret, ret));
}

}


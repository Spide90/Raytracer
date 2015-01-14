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
	return RGBColor::rep(1.f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return RGBColor(0, 0, 0);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(
		const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	float ueta = 1.f / eta;
	float nI = 1.f;
	float nT = eta;
	Vector unormal = normal;

	float cosI = dot(unormal, outDir.normalize());
	if(cosI < 0.f){
		unormal = -unormal;
		nI = eta;
		nT = 1.f;
		ueta = eta;
		cosI = -cosI;
	}

	float sinT = ueta * ueta * (1.f - cosI * cosI);

	if(sinT > 1.f){
		Vector ri = -outDir + 2 * dot(outDir, unormal)* unormal;
		return SampleReflectance(ri.normalize(), RGBColor(1.f, 1.f, 1.f));
	}

	float cosT = sqrtf(1.f - sinT);

	float rPar = (nT * cosI - nI * cosT) / (nT * cosI + nI * cosT);
	float rOrt = (nI * cosI - nT * cosT) / (nI * cosI + nT * cosT);

	float r = (rPar * rPar + rOrt * rOrt) / 2.f;

	float blubb = random();
	if (blubb < 0.5){ //reflection
		Vector ri = -outDir + 2 * dot(outDir, unormal)* unormal;
		return SampleReflectance(ri.normalize(), RGBColor::rep(2.f * r));
	}
	else{
		Vector trans = -outDir * ueta + unormal * (ueta * cosI - cosT);
		return SampleReflectance(trans.normalize(), RGBColor::rep((1.f - r) * 2.f));
	}
}

}


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

//	Vector unormal = normal;
//	float ueta = 1 / eta;
//	float n1 = 1.f;
//	float n2 = 1 / ueta;
//
//	float cosI = dot(inDir, unormal);
//
//	if (cosI > 0) {
//		cosI = dot(inDir, -unormal);
//		n2 = 1.f;
//		n1 = 1 / ueta;
//		ueta = 1 / ueta;
//	}
//
//	float sinT2 = ueta * ueta * (1.f - cosI * cosI);
//
//	if (sinT2 > 1.f) {
//		return RGBColor(0.f, 0.f, 0.f);
//	}
//
//	float cosT = sqrtf(1.f - sinT2);
//
//	float rOrth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
//	float rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
//
//	float retCol = (rOrth * rOrth + rPar * rPar);
//
//	return RGBColor::rep(retCol);

//	float cosI = dot(inDir, normal);
//	float ueta = eta;
//	Vector unormal = normal;
//	float n1 = 1.f;
//	float n2 = 1.f / ueta;
//
//	if(cosI < 0){
//		unormal = -unormal;
//		cosI = dot(inDir, unormal);
//		n1 = 1 / ueta;
//		n2 = 1.f;
//		ueta = 1 / ueta;
//	}
//
//	float sinI2 = ueta * ueta * (1 - cosI * cosI);
//
//	if(sinI2 > 1.f){
//		return RGBColor(1.f, 1.f, 1.f);
//	}
//
//	float cosT = sqrtf(1 - sinI2);
//
//	float r_Orth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
//	float r_Par = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
//
//	float ret = (r_Orth * r_Orth + r_Par * r_Par) * 0.5;
//
//	return RGBColor(ret, ret, ret);

//	return RGBColor(1.f, 1.f, 1.f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return RGBColor(0, 0, 0);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(
		const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	float m_eta = eta;
			Vector norm = normal;
			float nInc = 1;
			float nTrans = m_eta;

			float cosInc = dot(normal, -outDir);
			float sinInc = sqrt(1 - cosInc * cosInc);

			if (cosInc < 0){ //angle greater 90°
				norm = -normal;
				nInc = m_eta;
				nTrans = 1;
				m_eta = 1 / m_eta;
				cosInc = -cosInc;
			}

			float sinTrans = sinInc * m_eta;
			float cosTrans = sqrt(1 - sinTrans*sinTrans);

			float rpar = (nTrans* cosInc - nInc * cosTrans) / (nTrans* cosInc + nInc * cosTrans);
			float rort = (nInc * cosInc - nTrans * cosTrans) / (nInc * cosInc + nTrans * cosTrans);

			float r = (rpar *rpar + rort*rort) / 2;


			if (sinInc > (1/m_eta)){// totale innere Reflexion
				Vector ri = -outDir + 2 * dot(outDir, norm)* norm;
				return SampleReflectance(ri, RGBColor(1, 1, 1));
			}

			float rand = random();
			if (rand < 0.5){ //reflection
				Vector ri = -outDir + 2 * dot(outDir, normal)* normal;
				return SampleReflectance(ri, RGBColor::rep(2*r));
			}
			else{
				Vector trans = -outDir *m_eta + norm * (m_eta* cosInc - cosTrans);
				return SampleReflectance(trans, RGBColor::rep((1-r)*2));
			}

//	float ueta = eta;
//	Vector unormal = normal;
//	float nInc = 1.f;
//	float nTrans = eta;
//
//	float cosInc = dot(unormal, outDir);
//	float sinInc = sqrt(1 - cosInc * cosInc);
//
//	if (cosInc < 0) { //angle greater 90°
//		unormal = -normal;
//		ueta = 1.f / eta;
//		nInc = eta;
//		nTrans = 1.f;
//		cosInc = -cosInc;
//	}
//
//	float sinTrans = sinInc * ueta;
//	float cosTrans = sqrt(1 - sinTrans * sinTrans);
//
//	float rpar = (nTrans * cosInc - nInc * cosTrans)
//			/ (nTrans * cosInc + nInc * cosTrans);
//	float rort = (nInc * cosInc - nTrans * cosTrans)
//			/ (nInc * cosInc + nTrans * cosTrans);
//
//	float r = (rpar * rpar + rort * rort) / 2;
//
//	if (sinInc > (1 / ueta)) { // totale innere Reflexion
//		Vector ri = -outDir + 2 * dot(outDir, unormal) * unormal;
//		return SampleReflectance(ri, RGBColor(1.f, 1.f, 1.f));
//	}
//
//	float rand = random();
//	if (rand < 0.5) { //reflection
//		Vector ri = -outDir + 2 * dot(outDir, normal) * normal;
//		return SampleReflectance(ri, RGBColor::rep(2 * r));
//	} else {
//		Vector trans = -outDir * ueta + unormal * (ueta * cosInc - cosTrans);
//		return SampleReflectance(trans, RGBColor::rep((1 - r) * 2));
//	}

//	float ueta = 1 / eta;
//	Vector unormal = normal;
//	float blubb = random();
//
//	if (dot(outDir, unormal) < 0) {
//		//inside and go outside
//		unormal = -unormal;
//		ueta = 1 / ueta;
//	}
//
//	if (blubb < 0.5) {
//		//mirror
//
//		Vector dir = (2 * dot(outDir, unormal) * unormal - outDir).normalize();
//
//		float e2_k2 = (ueta * ueta);
//		float cosine = dot(dir, unormal);
//		float cosine_2 = cosine * cosine;
//		float r_par_2 = (e2_k2 * cosine_2 - 2 * ueta * cosine + 1) / (e2_k2 * cosine_2 + 2 * ueta * cosine + 1);
//		float r_per_2 = (e2_k2 - 2 * ueta * cosine + cosine_2) / (e2_k2 + 2 * ueta * cosine + cosine_2);
//
//		RGBColor ret = RGBColor(r_par_2 + r_per_2, r_par_2 + r_per_2, r_par_2 + r_per_2);
//
//		return Material::SampleReflectance(dir, ret);
//
////		return Material::SampleReflectance(dir, this->getReflectance(texPoint, unormal, outDir, dir));
//	} else {
//		//refraction
//		float cosI = dot(outDir, unormal);
//
//		float sinT2 = ueta * ueta * (1.f - cosI * cosI);
//
//		//TIR
//		if (sinT2 > 1.f) {
//			return Material::SampleReflectance();
//		}
//
//		float cosT = sqrtf(1.f - sinT2);
//
//		Vector dir = (ueta * cosI - cosT) * unormal - ueta * outDir;
//
//		return Material::SampleReflectance(dir, this->getReflectance(texPoint, normal, outDir, dir));
//	}

//	Vector unormal = normal;
//	Vector dir;
//	float ueta = eta;
//	float n1 = 1.f;
//	float n2 = 1.f / ueta;
//
//	float cosI = dot(outDir, unormal);
//
//	if(cosI < 0){
//		cosI = -dot(outDir, unormal);
//		n1 = 1 / ueta;
//		n2 = 1.f;
//		ueta = 1 / ueta;
//	}
//
//	float sinI2 = ueta * ueta * (1 - cosI * cosI);
//
//	if (sinI2 > 1.f) {
////		Vector ndir = (2 * dot(outDir, unormal) * unormal - outDir).normalize();
//		return Material::SampleReflectance();//ndir, RGBColor(1.f, 1.f, 1.f));
//	}
//
//	float cosT = sqrtf(1 - sinI2);
//
//	float r_Orth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
//	float r_Par = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
//
//	float ret = (r_Orth * r_Orth + r_Par * r_Par) * 0.5;
//
//	float blubb = random();
//
//	if (blubb < 0.5) {
//		dir = (2 * dot(outDir, unormal) * unormal - outDir).normalize();
//		return Material::SampleReflectance(dir,
//				RGBColor(ret, ret, ret));
////		return Material::SampleReflectance(dir,
////						(this->getReflectance(texPoint, unormal, outDir, dir)));
//	} else {
//		dir = (-ueta * outDir
//				+ (ueta * cosI - cosT) * unormal).normalize();
////		ret = 1 - ret;
//		return Material::SampleReflectance(dir,
//				(this->getReflectance(texPoint, -unormal, outDir, dir)));
//	}
////	return Material::SampleReflectance(dir,
////			2.f * RGBColor(ret, ret, ret));
}

}


/*
 * phong.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/phong.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <math.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent): specular(specular), exponent(exponent) {

}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	//Vector H = (inDir + outDir) / (inDir + outDir).length();
	Vector RI = (2*dot(inDir, normal)*normal - inDir).normalize();
	//float refl = powf(dot(H, normal), exponent) / (M_PI);
	float refl = powf(dot(RI, outDir), exponent);// / (2 * M_PI);
	return (specular->getColor(texPoint)) * refl;
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor(0,0,0);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return Material::SampleReflectance(normal, RGBColor(0, 0, 0));
}

Material::Sampling PhongMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}


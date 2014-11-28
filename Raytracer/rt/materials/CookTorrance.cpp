/*
 * CookTorrance.cpp
 *
 *  Created on: 28.11.2014
 *      Author: chris
 */

#include <rt/materials/cookTorrance.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <vector>
#include <core/color.h>
#include <math.h>

namespace rt {

CookTorranceMaterial::CookTorranceMaterial(Texture* texture, float diffuseFraction, float fresnelReflectance,
		float roughnessFraction) :
		texture(texture), diffuseFraction(diffuseFraction), fresnelReflectance(fresnelReflectance), roughnessFraction(
				roughnessFraction) {

}

RGBColor CookTorranceMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	RGBColor diffuseColor = diffuseFraction * (texture->getColor(texPoint) * dot(inDir.normalize(), normal) / M_PI);

	Vector halfVector = (inDir + outDir).normalize();

	float angleNormalInDir = std::max(dot(normal, inDir), 0.f);
	float angleNormalHalf = std::max(dot(normal, halfVector), 0.f);
	float angleNormalOutDir = std::max(dot(normal, outDir), 0.f);
	float angleOutDirHalf = std::max(dot(outDir, halfVector), 0.f);

	float fresnel = fresnelReflectance + (1 - fresnelReflectance) * powf(1 - angleNormalHalf, 5);

	float roughness = 1.f / (4.f * roughnessFraction * roughnessFraction * powf(angleNormalHalf, 4))
			* exp(
					(angleNormalHalf * angleNormalHalf - 1)
							/ (roughnessFraction * roughnessFraction * angleNormalHalf * angleNormalHalf));

	float geometricalAttenuiation = std::min(1.f,
			std::min((2 * angleNormalHalf * angleNormalOutDir) / angleNormalHalf,
					(2 * angleNormalHalf * angleNormalInDir) / angleNormalHalf));

	RGBColor specular = (1 - diffuseFraction) * texture->getColor(texPoint) * fabs(dot(inDir, normal)) * (fresnel * roughness * geometricalAttenuiation)
			/ (angleNormalOutDir * angleNormalOutDir * M_PI);

	return diffuseColor + specular;
}

RGBColor CookTorranceMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor(0, 0, 0);
}

Material::SampleReflectance CookTorranceMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return SampleReflectance();
}

Material::Sampling CookTorranceMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}


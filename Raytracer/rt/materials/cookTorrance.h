/*
 * cookTorrance.h
 *
 *  Created on: 28.11.2014
 *      Author: chris
 */

#ifndef RT_MATERIALS_COOKTORRANCE_H_
#define RT_MATERIALS_COOKTORRANCE_H_

#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <vector>

namespace rt {

class CookTorranceMaterial: public Material {
public:

	Texture* texture;

	float diffuseFraction;
	float fresnelReflectance;
	float roughnessFraction;

	CookTorranceMaterial(Texture* texture, float diffuseFraction, float fresnelReflectance, float roughnessFraction);
	virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
	virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
	virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
	virtual Sampling useSampling() const;
};

}

#endif /* RT_MATERIALS_COOKTORRANCE_H_ */

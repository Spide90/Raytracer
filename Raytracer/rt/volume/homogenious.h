/*
 * homogenious.h
 *
 *  Created on: 23.01.2015
 *      Author: chris
 */

#ifndef RT_VOLUME_HOMOGENIOUS_H_
#define RT_VOLUME_HOMOGENIOUS_H_

#include <rt/volume/fog.h>
#include <core/color.h>
#include <rt/primitive.h>
#include <rt/materials/material.h>

namespace rt {

class HomogeniousFog: public Fog {
public:

	float density;
	Material* fogMaterial;
	Primitive* prim;

	HomogeniousFog(Primitive* prim, float density, Material* material);

	virtual RGBColor getColor(Point hitPoint, Vector normal, Vector inDir, Vector outDir);

	virtual float transmittance(Point origin, Point hitPoint);

	virtual float getDensity(Point point);

	virtual Primitive* getPrimitive();
};

}

#endif /* RT_VOLUME_HOMOGENIOUS_H_ */

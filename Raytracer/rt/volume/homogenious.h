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
	RGBColor fogColor;
	Primitive* prim;

	HomogeniousFog(Primitive* prim, float density, RGBColor fogColor);

	virtual RGBColor getColor(Point hitPoint);

	virtual float transmittance(Point origin, Point hitPoint);

	virtual float getDensity(Point point);

	virtual Primitive* getPrimitive();
};

}

#endif /* RT_VOLUME_HOMOGENIOUS_H_ */

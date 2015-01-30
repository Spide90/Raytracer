/*
 * fog.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#ifndef RT_VOLUME_FOG_H_
#define RT_VOLUME_FOG_H_

#include <core/color.h>
#include <rt/primitive.h>
#include <core/point.h>

namespace rt {

class Fog {
public:

	virtual RGBColor getColor(Point hitPoint) = 0;

	virtual float transmittance(Point origin, Point hitPoint) = 0;

	virtual float getDensity(Point point) = 0;

	virtual Primitive* getPrimitive() = 0;
};

}

#endif /* RT_VOLUME_FOG_H_ */

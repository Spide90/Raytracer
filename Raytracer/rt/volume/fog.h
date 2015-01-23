/*
 * fog.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#ifndef RT_VOLUME_FOG_H_
#define RT_VOLUME_FOG_H_

#include <core/color.h>
#include <core/point.h>

namespace rt {

class Fog {
public:

	virtual RGBColor getColor(Point hitPoint, Vector normal, Vector inDir, Vector outDir) = 0;

	virtual float transmittance(Point origin, Point hitPoint) = 0;

	virtual float getDensity(Point point) = 0;
};

}

#endif /* RT_VOLUME_FOG_H_ */

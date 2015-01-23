/*
 * AmbientHomogenius.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include <rt/volume/fog.h>
#include <core/color.h>

namespace rt {

class AmbientHomogeniousFog : public Fog {
public:

	float density;
	RGBColor ambientLightColor;

	AmbientHomogeniousFog(float density, RGBColor ambientLightColor);

	virtual RGBColor getColor(Point hitPoint, Vector normal, Vector inDir, Vector outDir);

	virtual float transmittance(Point origin, Point hitPoint);

	virtual float getDensity(Point point);
};

}



/*
 * ambient.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#ifndef RT_LIGHTS_AMBIENT_H_
#define RT_LIGHTS_AMBIENT_H_

#include <core/color.h>
#include <rt/lights/light.h>

namespace rt {

class AmbientLight : public Light {
public:

	RGBColor intensity;

	AmbientLight() {}
	AmbientLight(const RGBColor& intensity);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}



#endif /* RT_LIGHTS_AMBIENT_H_ */

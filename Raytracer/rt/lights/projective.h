/*
 * projective.h
 *
 *  Created on: 21.11.2014
 *      Author: chris
 */

#ifndef RT_LIGHTS_PROJECTIVE_H_
#define RT_LIGHTS_PROJECTIVE_H_

#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>

namespace rt {

class ProjectiveLight : public Light {
public:

	Point position;
	RGBColor intensity;

	ProjectiveLight() {}
	ProjectiveLight(const Point& position, RGBColor intensity);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}



#endif /* RT_LIGHTS_PROJECTIVE_H_ */

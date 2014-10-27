/*
 * orthographic.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <rt/cameras/orthographic.h>
#include <rt/ray.h>
#include <core/point.h>

namespace rt {

OrthographicCamera::OrthographicCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float scaleX,
        float scaleY
        ) : center(center), forward(forward), up(up), scaleX(scaleX), scaleY(scaleY){
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
	//TODO fix me
	return Ray(center, forward);
}

}

/*
 * orthographic.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <rt/cameras/orthographic.h>
#include <rt/ray.h>
#include <core/point.h>
#include <core/vector.h>

#include <stdio.h>

namespace rt {

OrthographicCamera::OrthographicCamera(
        const Point& center,
        const Vector& forw,
        const Vector& upVector,
        float scaleX,
        float scaleY
        ) : center(center), scaleX(scaleX), scaleY(scaleY) {
	forward = forw.normalize();
	up = upVector.normalize();
	imageX = (up * (dot(up, forward)) - cross(up, forward)).normalize() * scaleX;
	imageY = cross(forward, imageX).normalize() * scaleY;
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
	return Ray(center + (y * imageY)  + (x * imageX), forward);
}

}

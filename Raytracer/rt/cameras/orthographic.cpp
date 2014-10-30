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
#include <math.h>

#include <stdio.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forw, const Vector& upVector, float scaleX,
		float scaleY) :
		center(center), scaleX(scaleX), scaleY(scaleY) {
	forward = forw.normalize();
	up = upVector;
	imageY = (forward - (dot(forward, forward) / dot(forward, up)) * up).normalize() * forward.length() * 0.5 * scaleY;
	imageX = cross(imageY, forward).normalize() * forward.length() * 0.5 * scaleX;
//	imageX = (up * (dot(up, forward)) - cross(forward, up)).normalize() * 0.5 * scaleX;
//	imageY = cross(imageX, forward).normalize() * 0.5 * scaleY;
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
	return Ray(center + (y * imageY) + (x * imageX), forward);
}

}

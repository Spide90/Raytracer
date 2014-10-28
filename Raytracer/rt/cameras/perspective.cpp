/*
 * perspective.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <rt/cameras/perspective.h>
#include <rt/ray.h>
#include <math.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forw,
		const Vector& upVector, float verticalOpeningAngle,
		float horizonalOpeningAngle) :
		center(center), verticalOpeningAngle(verticalOpeningAngle), horizontalOpeningAngle(
				horizontalOpeningAngle) {
	forward = forw;
	up = upVector;
	imageX = (up * (dot(up, forward)) - cross(up, forward)).normalize() * 0.5 * horizonalOpeningAngle;
	imageY = cross(forward, imageX).normalize() * 0.5 * verticalOpeningAngle;

}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
	//TODO implement me
	return Ray(center, forward + x * imageX + y * imageY);
}

}


/*
 * perspective.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <rt/cameras/perspective.h>
#include <rt/ray.h>
#include <math.h>

#include <stdio.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forw, const Vector& upVector, float verticalAngle,
		float horizontalAngle) :
		center(center), verticalOpeningAngle(verticalAngle), horizontalOpeningAngle(horizontalAngle) {
	forward = forw.normalize();
	up = upVector.normalize();
/*	if (dot(forward, up) != 0) {
		imageY = -(forward - (dot(forward, forward) / dot(forward, up)) * up).normalize() * forward.length()
				* tan(0.5 * verticalOpeningAngle);
		imageX = cross(imageY, forward).normalize() * forward.length() * tan(0.5 * horizontalOpeningAngle);
	} else {*/
		imageX = cross(forward, up).normalize() * tan(0.5 * horizontalOpeningAngle);
		imageY = cross(forward, imageX).normalize() * tan(0.5 * verticalOpeningAngle);
//	}
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
	Ray ray(center, (forward + (x * imageX) + (y * imageY)).normalize());
	return ray;
}

}


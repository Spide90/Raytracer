/*
 * fisheye.cpp
 *
 *  Created on: 30.10.2014
 *      Author: chris
 */

#include <rt/cameras/fisheye.h>
#include <rt/ray.h>
#include <core/point.h>
#include <core/vector.h>
#include <math.h>

#include <stdio.h>

namespace rt {

FisheyeCamera::FisheyeCamera(const Point& center, const Vector& forw, const Vector& upVector, float horizontalAngle,
		float verticalAngle, float aspectRatio) :
		center(center), verticalAngle(verticalAngle), horizontalAngle(horizontalAngle), aspectRatio(aspectRatio) {
	forward = forw.normalize();
	up = upVector;
	imageY = (forward - (dot(forward, forward) / dot(forward, up)) * up).normalize() * forward.length()
			* tan(0.5 * verticalAngle);
	imageX = cross(imageY, forward).normalize() * forward.length() * tan(0.5 * horizontalAngle);
}

Ray FisheyeCamera::getPrimaryRay(float x, float y) const {
	return Ray(center, (sin(horizontalAngle) * x * imageX + sin(verticalAngle) * y * imageY - cos(horizontalAngle) * forward).normalize());
}

}

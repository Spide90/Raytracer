/*
 * dofperspective.cpp
 *
 *  Created on: 07.01.2015
 *      Author: chris
 */

#include <rt/cameras/dofperspective.h>
#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>
#include <core/random.h>
#include <core/float4.h>

#include <math.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up,
		float verticalOpeningAngle, float horizonalOpeningAngle, float focalDistance, float apertureRadius) :
		center(center), forward(forward), up(up), verticalOpeningAngle(verticalOpeningAngle), horizontalOpeningAngle(
				horizonalOpeningAngle), focalDistance(focalDistance), apertureRadius(apertureRadius) {
	if (dot(forward, up) != 0) {
		imageY = -(forward - (dot(forward, forward) / dot(forward, up)) * up).normalize() * forward.length()
				* tan(0.5 * verticalOpeningAngle);
		imageX = cross(imageY, forward).normalize() * forward.length() * tan(0.5 * horizontalOpeningAngle);
	} else {
		imageX = cross(forward, up).normalize() * tan(0.5 * horizontalOpeningAngle);
		imageY = cross(forward, imageX).normalize() * tan(0.5 * verticalOpeningAngle);
	}
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
	Vector direction = forward + (x * imageX) + (y * imageY);
	float length = direction.length();
	if (direction.length() != focalDistance) {
		float random1 = random(2) - 1;
		float random2 = random(2) - 1;
		Point dofPertubation = center + (random1 * apertureRadius * imageX / imageX.length()) + (random2 * apertureRadius * imageY / imageY.length());
		//LOG_DEBUG("original center: " << center.x << ", " << center.y << ", " << center.z);
		//LOG_DEBUG("dof pertubation: " << dofPertubation.x << ", " << dofPertubation.y << ", " << dofPertubation.z);
		Point h = center + direction;
		return Ray(dofPertubation, (h - dofPertubation).normalize());
	} else {
		return Ray(center, direction.normalize());
	}
}

}


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

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center,
		const Vector& forward, const Vector& up, float verticalOpeningAngle,
		float horizonalOpeningAngle, float focalDistance, float apertureRadius) :
		center(center), forward(forward), up(up), verticalOpeningAngle(
				verticalOpeningAngle), horizontalOpeningAngle(
				horizonalOpeningAngle), focalDistance(focalDistance), apertureRadius(
				apertureRadius) {

}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
	//TODO implement me!
}

}


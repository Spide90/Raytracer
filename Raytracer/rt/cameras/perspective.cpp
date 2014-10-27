/*
 * perspective.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <rt/cameras/perspective.h>
#include <rt/ray.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward,
		const Vector& up, float verticalOpeningAngle,
		float horizonalOpeningAngle) :
		center(center), forward(forward), up(up), verticalOpeningAngle(
				verticalOpeningAngle), horizontalOpeningAngle(
				horizontalOpeningAngle) {
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
	//TODO implement me
}

}


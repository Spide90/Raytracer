/*
 * ray.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <rt/ray.h>

namespace rt {

Ray::Ray(const Point& origin, const Vector& direction) : o(origin), d(direction) {

}

Point Ray::getPoint(float distance) const {
	return (o + d) * distance;
}

}


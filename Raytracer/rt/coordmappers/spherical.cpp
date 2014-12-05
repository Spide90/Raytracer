/*
 * sphereical.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/spherical.h>
#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>
#include <math.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper() {

}

SphericalCoordMapper::SphericalCoordMapper(const Point& origin,
		const Vector& zenith, const Vector& azimuthRef) :
		origin(origin), zenith(zenith), aziRef(azimuthRef) {
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
	Vector PO = hit.local() - origin;
	float rho = PO.length();
	float phi = dot(zenith.normalize(), PO.normalize());
	Point Q = hit.local() - phi * zenith.normalize();
	float theta = dot(Q - origin, aziRef);

	return Point(rho * theta * sinf(acosf(phi)), rho * sinf(acosf(phi)) * sinf(acosf(theta)), rho * phi);
}

}


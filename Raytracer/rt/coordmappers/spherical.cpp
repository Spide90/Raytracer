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
	Vector zAx = cross(zenith.normalize(), aziRef.normalize()).normalize() * aziRef.length();

	float theta = acosf(dot(PO.normalize(), zenith.normalize()));

	float u = dot(PO, aziRef) / aziRef.lensqr();
	float v = dot(PO, zAx) / zAx.lensqr();

	Vector proHit(u, 0.f, v);

	float phi = acosf(dot(proHit.normalize(), aziRef.normalize()));

	return Point( phi / (2 * M_PI * aziRef.length()), theta / (M_PI * aziRef.length()), 0.f);
}

}


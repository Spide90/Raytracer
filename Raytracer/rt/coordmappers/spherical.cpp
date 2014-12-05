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
}

}


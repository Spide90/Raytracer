/*
 * plane.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/plane.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>
#include <core/float4.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2): e1(e1), e2(e2) {
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
	Vector normal = cross(e1, e2).normalize();

	Point proj = hit.local() - dot(hit.normal(), normal) * normal;

	return proj;
}

}


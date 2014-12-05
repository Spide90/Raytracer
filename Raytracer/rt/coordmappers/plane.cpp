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

	Float4 f4 = Float4(hit.localPoint.x * e1) + Float4(hit.localPoint.y * e2);
	f4.w = 1;
	f4.z = 0;

	return Point(f4);
}

}


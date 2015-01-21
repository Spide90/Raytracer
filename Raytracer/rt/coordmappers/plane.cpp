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
	Vector hitdir = hit.local() - Point(0,0,0);

	float u = dot(hitdir, e1) / e1.lensqr();
	float v = dot(hitdir, e2) / e2.lensqr();

	return Point(u,v,0);
}

}

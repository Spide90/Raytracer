/*
 * tmapper.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/tmapper.h>
#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>
#include <core/float4.h>

namespace rt {

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1,
		const Point& tv2) :
		edge1(tv0), edge2(tv1), edge3(tv2) {

}

TriangleMapper::TriangleMapper(Point ntv[3]) :
		edge1(ntv[0]), edge2(ntv[1]), edge3(ntv[2]) {

}

Point TriangleMapper::getCoords(const Intersection& hit) const {
	Float4 f4 = hit.localPoint.x * Float4(edge1) + hit.localPoint.y * Float4(edge2) + hit.localPoint.z * Float4(edge3);
	f4.w = 1;
	return Point(f4);
}

}


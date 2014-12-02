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

namespace rt {

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2) {

}

TriangleMapper::TriangleMapper(Point ntv[3]) {

}

Point TriangleMapper::getCoords(const Intersection& hit) const {

}

}


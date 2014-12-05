/*
 * cylindrical.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/cylindrical.h>
#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis): origin(origin), longAxe(longitudinalAxis), polAxe(polarAxis) {

}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {

}

}


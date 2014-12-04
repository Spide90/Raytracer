/*
 * world.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/world.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

WorldMapper::WorldMapper() {

}

WorldMapper::WorldMapper(const Float4& scale): scale(scale) {
}

Point WorldMapper::getCoords(const Intersection& hit) const {
	return Point(Float4(hit.point) * scale);
}

}


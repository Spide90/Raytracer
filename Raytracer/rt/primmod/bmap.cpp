/*
 * bmap.cpp
 *
 *  Created on: 14.01.2015
 *      Author: chris
 */

#include <rt/primmod/bmap.h>
#include <vector>
#include <rt/primitive.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/bbox.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3,
		float vscale) {
}

BBox BumpMapper::getBounds() const {

}

Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {

}

void BumpMapper::setMaterial(Material* m) {

}

void BumpMapper::setCoordMapper(CoordMapper* cm) {

}

Point BumpMapper::getCenterPoint() {

}
}


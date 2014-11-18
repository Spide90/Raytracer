/*
 * simpleGroup.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/groups/simplegroup.h>
#include <vector>
#include <rt/groups/group.h>
#include <rt/intersection.h>
#include <rt/bbox.h>

#include <stdio.h>

namespace rt {

BBox SimpleGroup::getBounds() const {

}

Intersection SimpleGroup::intersect(const Ray& ray, float previousBestDistance) const {
	Intersection bestIntersection = Intersection::failure();
	float bestDistance = previousBestDistance;
	for (int i = 0;  i < primitives.size(); i++) {
		Intersection intersection = primitives[i]->intersect(ray, bestDistance);
		if (intersection) {
			bestIntersection = intersection;
			bestDistance = intersection.distance;
		}
	}
	return bestIntersection;
}

void SimpleGroup::rebuildIndex() {

}

void SimpleGroup::add(Primitive* p) {
	primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
	for (int i = 0; i < primitives.size(); i++) {
		primitives[i]->setMaterial(m);
	}

}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {

}

Point SimpleGroup::getCenterPoint() {
	return Point(0, 0, 0);
}

}


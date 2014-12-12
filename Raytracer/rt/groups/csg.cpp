/*
 * csg.cpp
 *
 *  Created on: 12.12.2014
 *      Author: chris
 */

#include <rt/groups/csg.h>
#include <rt/groups/group.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/bbox.h>

namespace rt {

ConstructiveSolidGeometry::ConstructiveSolidGeometry(Operator op) :
		op(op) {
	left = nullptr;
	right = nullptr;
}

BBox ConstructiveSolidGeometry::getBounds() const {

}

Intersection ConstructiveSolidGeometry::intersect(const Ray& ray,
		float previousBestDistance) const {
	Intersection leftIntersection = left->intersect(ray, previousBestDistance);
	Intersection rightIntersection = right->intersect(ray, previousBestDistance);
	switch (op) {
	case UNION:
			if (leftIntersection.distance < rightIntersection.distance) {
				return leftIntersection;
			} else {
				return rightIntersection;
		}
		break;
	case INTERSECTION:
		if (leftIntersection.distance)
		/*
		for (int i = 0; i < primitives.size(); i++) {
			intersection = primitives[i]->intersect(ray, previousBestDistance);
			if (intersection) {
				bestIntersection = intersection;
			} else {
				return Intersection::failure();
			}
		}
		return bestIntersection;*/
		break;
	case DIFFERENCE:
		/*
		//substract all from first element
		intersection = primitives[0]->intersect(ray, previousBestDistance);
		for (int i = 1; i < primitives.size(); i++) {
			intersection = primitives[i]->intersect(ray, previousBestDistance);
			if (intersection) {
				return Intersection::failure();
			}
		}
		return intersection;*/
		break;
	default:
		break;
	}
	return Intersection::failure();
}

void ConstructiveSolidGeometry::rebuildIndex() {

}

void ConstructiveSolidGeometry::add(Primitive* p) {
	if (left == nullptr) {
		left = p;
		return;
	}
	if (right == nullptr) {
		right = p;
		return;
	}
	LOG_DEBUG("adding to much primitives to one csg!");
}

void ConstructiveSolidGeometry::addLeft(Primitive* p) {
	left = p;
}

void ConstructiveSolidGeometry::addRight(Primitive* p) {
	right = p;
}

void ConstructiveSolidGeometry::setMaterial(Material* m) {
	material = m;
}

void ConstructiveSolidGeometry::setCoordMapper(CoordMapper* cm) {
	coordMapper = cm;
}

Point ConstructiveSolidGeometry::getCenterPoint() {
	//not used
	LOG_DEBUG("blubb");
}

}


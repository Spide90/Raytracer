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
	Intersection rightIntersection = right->intersect(ray,
			previousBestDistance);
	switch (op) {
	case UNION:
		if (leftIntersection.distance < rightIntersection.distance) {
			return leftIntersection;
		} else {
			return rightIntersection;
		}
		break;
	case INTERSECTION:
		if (leftIntersection.distance < rightIntersection.distance) {
			if (leftIntersection.exitDistance > rightIntersection.distance) {
				return rightIntersection;
			} else {
				return Intersection::failure();
			}
		} else {
			if (rightIntersection.exitDistance > leftIntersection.distance) {
				return leftIntersection;
			} else {
				return Intersection::failure();
			}
		}
		break;
	case DIFFERENCE:
		if (leftIntersection && rightIntersection) {
			//left - right
			if (leftIntersection.distance < rightIntersection.distance) {
				//TODO maybe do the computaion as well ?
				return leftIntersection;
			} else {
				if (rightIntersection.exitDistance
						>= leftIntersection.distance) {
					Intersection resultIntersection(
							rightIntersection.exitDistance, ray,
							rightIntersection.solid,
							-rightIntersection.normalVector,
							ray.o + ray.d * rightIntersection.exitDistance,
							leftIntersection.exitDistance);
					if (leftIntersection.exitDistance < resultIntersection.distance) {
						return Intersection::failure();
					}
					return resultIntersection;
				} else {
					return leftIntersection;
				}
			}
		} else {
			if (leftIntersection) {
				return leftIntersection;
			} else {
				return Intersection:: failure();
			}
		}
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


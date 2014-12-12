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

}

BBox ConstructiveSolidGeometry::getBounds() const {

}

Intersection ConstructiveSolidGeometry::intersect(const Ray& ray,
		float previousBestDistance) const {
	Intersection intersection = intersection.failure();
	Intersection bestIntersection = Intersection::failure();
	float bestDistance = previousBestDistance;
	switch (op) {
	case UNION:
		for (int i = 0; i < primitives.size(); i++) {
			intersection = primitives[i]->intersect(ray, previousBestDistance);
			if (intersection && intersection.distance < bestDistance) {
				bestIntersection = intersection;
				bestDistance = intersection.distance;
			}
		}
		return bestIntersection;
		break;
	case INTERSECTION:
		for (int i = 0; i < primitives.size(); i++) {
			intersection = primitives[i]->intersect(ray, bestDistance);
			if (intersection) {
				if (intersection.distance <= bestDistance) {
					bestIntersection = intersection;
					bestDistance = intersection.distance;
				}
			} else {
				return Intersection::failure();
			}
		}
		return bestIntersection;
		break;
	case DIFFERENCE:
		//substract all from first element
		intersection = primitives[0]->intersect(ray, previousBestDistance);
		for (int i = 1; i < primitives.size(); i++) {
			intersection = primitives[i]->intersect(ray, previousBestDistance);
			if (intersection) {
				return Intersection::failure();
			}
		}
		return intersection;
		break;
	default:
		break;
	}
	return Intersection::failure();
}

void ConstructiveSolidGeometry::rebuildIndex() {

}

void ConstructiveSolidGeometry::add(Primitive* p) {
	primitives.push_back(p);
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


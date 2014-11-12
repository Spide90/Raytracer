/*
 * BVHInnerNode.cpp
 *
 *  Created on: 12.11.2014
 *      Author: chris
 */

#include <rt/groups/BVHInnerNode.h>
#include <vector>
#include <rt/groups/bvhNode.h>
#include <rt/bbox.h>
#include <rt/primitive.h>

namespace rt {

BBox BVHInnerNode::getBounds() const {
	return boundingBox;
}

Intersection BVHInnerNode::intersect(const Ray& ray, float previousBestDistance) const {
	Intersection bestIntersection = Intersection::failure();
	float bestDistance = previousBestDistance;
	for (int i = 0; i < children.size(); i++) {
		auto boxIntersection = children[i]->getBounds().intersect(ray);
		if (boxIntersection.second < boxIntersection.first) {
			Intersection intersection = children[i]->intersect(ray, bestDistance);
			if (intersection) {
				bestIntersection = intersection;
				bestDistance = intersection.distance;
			}
		}
	}
	return bestIntersection;
}

void BVHInnerNode::rebuildIndex() {
	boundingBox = BBox::empty();
	for (int i = 0; i < children.size(); i++) {
		boundingBox.extend(children[i]->getBounds());
	}
}

void BVHInnerNode::add(BVHNode* p) {
	children.push_back(p);
}

void BVHInnerNode::setMaterial(Material* m) {

}

void BVHInnerNode::setCoordMapper(CoordMapper* cm) {

}

}


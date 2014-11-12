/*
 * BVHLeafNode.cpp
 *
 *  Created on: 12.11.2014
 *      Author: chris
 */

#include <rt/groups/BVHLeafNode.h>
#include <vector>
#include <rt/groups/bvhNode.h>
#include <rt/bbox.h>
#include <rt/primitive.h>

namespace rt {

BBox BVHLeafNode::getBounds() const {
	return boundingBox;
}

Intersection BVHLeafNode::intersect(const Ray& ray, float previousBestDistance) const {
	return primitive->intersect(ray, previousBestDistance);
}

void BVHLeafNode::rebuildIndex() {
	boundingBox = primitive->getBounds();
}

void BVHLeafNode::add(Primitive* p) {
	primitive = p;
}

void BVHLeafNode::setMaterial(Material* m) {

}

void BVHLeafNode::setCoordMapper(CoordMapper* cm) {

}

}


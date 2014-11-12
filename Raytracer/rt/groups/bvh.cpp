/*
 * bvh.cpp
 *
 *  Created on: 11.11.2014
 *      Author: chris
 */

#include <rt/groups/bvh.h>
#include <vector>
#include <rt/intersection.h>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <rt/groups/BVHInnerNode.h>
#include <float.h>
#include <math.h>

namespace rt {

#define MAX_PRIMITIVES 5

BVH::BVH() {
	leftChild = nullptr;
	rightChild = nullptr;

	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;

	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;
}

BBox BVH::getBounds() const {
	return boundingBox;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
	LOG_DEBUG("Intersection begin")
	std::cout << "intersection begin!\n";
	Intersection bestIntersection = Intersection::failure();
	float bestDistance = previousBestDistance;

	if (leftChild != nullptr) {
		std::pair<float, float> leftBoxIntersection = leftChild->getBounds().intersect(ray);
		if (leftBoxIntersection.second > leftBoxIntersection.first) {
			if ((leftBoxIntersection.first < previousBestDistance) && (leftBoxIntersection.first < bestDistance)) {
				LOG_DEBUG("better intersection found in left child!")
				bestIntersection = leftChild->intersect(ray, bestDistance);
			}
		}
	}
	if (rightChild != nullptr) {
		std::pair<float, float> rightBoxIntersection = rightChild->getBounds().intersect(ray);
		if (rightBoxIntersection.second < rightBoxIntersection.first) {
			if ((rightBoxIntersection.first < previousBestDistance) && (rightBoxIntersection.first < bestDistance)) {
				LOG_DEBUG("better intersection found in right child!")
				bestIntersection = rightChild->intersect(ray, bestDistance);
			}
		}
	}

	for (int i = 0; i < primitives.size(); i++) {
		Intersection intersection = primitives[i]->intersect(ray, bestDistance);
		if (intersection) {
			bestIntersection = intersection;
			bestDistance = intersection.distance;
		}
	}

	LOG_DEBUG("best intersection distance: " << bestDistance)
	return bestIntersection;
}

void BVH::rebuildIndex() {
	LOG_DEBUG("building index... current elements: " << primitives.size())
	if (primitives.size() > MAX_PRIMITIVES) {
		if (leftChild == nullptr) {
			LOG_DEBUG("creating left child")
			leftChild = new BVH();
		}
		if (rightChild == nullptr) {
			LOG_DEBUG("creating right child")
			rightChild = new BVH();
		}
		bool lower = false;
		LOG_DEBUG("everyday i'm shuffling!")
		while (primitives.size() > 0) {
			Primitive* primitive = primitives.back();
			primitives.pop_back();
			BBox primitiveBox = primitive->getBounds();
			float boxMiddleX;
			float boxMiddleY;
			float boxMiddleZ;

			switch (longestAxis) {
			case X:
				boxMiddleX = (primitiveBox.max.x + primitiveBox.min.x) / 2;
				lower = boxMiddleX < longestAxisLength;
				break;
			case Y:
				boxMiddleY = (primitiveBox.max.y + primitiveBox.min.y) / 2;
				lower = boxMiddleY < longestAxisLength;
				break;
			case Z:
				boxMiddleZ = (primitiveBox.max.z + primitiveBox.min.z) / 2;
				lower = boxMiddleZ < longestAxisLength;
				break;
			default:
				break;
			}

			if (lower) {
				LOG_DEBUG("putting primitive to left")
				leftChild->add(primitive);
			} else {
				LOG_DEBUG("putting primitive to right")
				rightChild->add(primitive);
			}
		}
		LOG_DEBUG("shuffle done... elements now" << primitives.size())
	}

	boundingBox = BBox::empty();
	if (leftChild != nullptr) {
		LOG_DEBUG("rebuilding left child index")
		leftChild->rebuildIndex();
		boundingBox.extend(leftChild->getBounds());
	}
	if (rightChild != nullptr) {
		LOG_DEBUG("rebuilding right child index")
		rightChild->rebuildIndex();
		boundingBox.extend(rightChild->getBounds());
	}
	LOG_DEBUG("building bounding box of current node")
	for (int i = 0; i < primitives.size(); ++i) {
		boundingBox.extend(primitives[i]->getBounds());
	}
}

BVH::~BVH() {

}

void BVH::add(Primitive* p) {
	primitives.push_back(p);

	BBox box = p->getBounds();
	float boxMiddleX = (box.max.x + box.min.x) / 2;
	float boxMiddleY = (box.max.y + box.min.y) / 2;
	float boxMiddleZ = (box.max.z + box.min.z) / 2;

	minX = minX > boxMiddleX ? boxMiddleX : minX;
	minY = minY > boxMiddleY ? boxMiddleY : minY;
	minZ = minY > boxMiddleZ ? boxMiddleZ : minZ;

	maxX = maxX < boxMiddleX ? boxMiddleX : maxX;
	maxY = maxY < boxMiddleY ? boxMiddleY : maxY;
	maxZ = maxZ < boxMiddleZ ? boxMiddleZ : maxZ;
	/*
	 minX = minX > box.min.x ? box.min.x : minX;
	 minY = minY > box.min.y ? box.min.y : minY;
	 minZ = minY > box.min.z ? box.min.z : minZ;

	 maxX = maxX < box.max.x ? box.max.z : maxX;
	 maxY = maxY < box.max.y ? box.max.z : maxY;
	 maxZ = maxZ < box.max.z ? box.max.z : maxZ;
	 */
	float lengthX = (maxX + minX) / 2;
	float lengthY = (maxY + minY) / 2;
	float lengthZ = (maxZ + minZ) / 2;
	if (lengthX >= lengthZ) {
		if (lengthX >= lengthY) {
			longestAxisLength = lengthX;
			longestAxis = X;
		} else {
			if (lengthZ >= lengthY) {
				longestAxisLength = lengthZ;
				longestAxis = Z;
			}
		}
	} else {
		if (lengthY >= lengthZ) {
			longestAxisLength = lengthY;
			longestAxis = Y;
		} else {
			longestAxisLength = lengthZ;
			longestAxis = Z;
		}
	}
}

void BVH::setMaterial(Material* m) {

}

void BVH::setCoordMapper(CoordMapper* cm) {

}

}


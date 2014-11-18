/*
 * bvh.cpp
 *
 *  Created on: 11.11.2014
 *      Author: chris
 */

#include <core/macros.h>
#include <core/point.h>
#include <rt/groups/bvh.h>
#include <rt/intersection.h>
#include <math.h>
#include <iostream>
#include <utility>
#include <rt/solids/solid.h>

namespace rt {

/**
 * max primitives per leaf
 */
#define MAX_PRIMITIVES 3

/**
 * number of bins for SAH
 */
#define BIN_COUNT 16

/**
 * float correction
 */
#define EPSILON 0.001

/*
 * in case i forget to ask this question in the email:
 * Did we receive any points for environment camera and/or fisheye camera ?
 */

BVH::BVH() {
	leftChild = nullptr;
	rightChild = nullptr;

	boundingBox = BBox::empty();
	totalArea = 0;
}

BBox BVH::getBounds() const {
	return boundingBox;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
	Intersection bestIntersection = Intersection::failure();
	float bestDistance = previousBestDistance;
	Intersection leftIntersection = Intersection::failure();
	if (leftChild != nullptr) {
		std::pair<float, float> leftBoxIntersection = leftChild->getBounds().intersect(ray);
		if ((leftBoxIntersection.first <= leftBoxIntersection.second) && (leftBoxIntersection.first < bestDistance)) {
			leftIntersection = leftChild->intersect(ray, bestDistance);
		}
	}
	Intersection rightIntersection = Intersection::failure();
	if (rightChild != nullptr) {
		std::pair<float, float> rightBoxIntersection = rightChild->getBounds().intersect(ray);
		if ((rightBoxIntersection.first <= rightBoxIntersection.second) && (rightBoxIntersection.first < bestDistance)) {
			rightIntersection = rightChild->intersect(ray, bestDistance);
		}
	}
	if (leftIntersection && rightIntersection) {
		bestIntersection = leftIntersection.distance < rightIntersection.distance ? leftIntersection : rightIntersection;
	} else {
		if (leftIntersection) {
			bestIntersection = leftIntersection;
		}
		if (rightIntersection) {
			bestIntersection = rightIntersection;
		}
	}
	if ((leftChild == nullptr) && (rightChild == nullptr)) {
		for (int i = 0; i < primitives.size(); i++) {
			Intersection intersection = primitives[i]->intersect(ray, bestDistance);
			if (intersection) {
				bestIntersection = intersection;
				bestDistance = intersection.distance;
			}
		}
	}
	return bestIntersection;
}

void BVH::rebuildIndex() {
	if (primitives.size() > MAX_PRIMITIVES) {
		float lengthX = boundingBox.max.x - boundingBox.min.x;
		float lengthY = boundingBox.max.y - boundingBox.min.y;
		float lengthZ = boundingBox.max.z - boundingBox.min.z;

		if (lengthX >= lengthY && lengthX >= lengthZ) {
			longestAxisLength = lengthX;
			longestAxis = X;	// X
		}
		if (lengthY >= lengthX && lengthY >= lengthZ) {
			longestAxisLength = lengthY;
			longestAxis = Y;	// Y
		}
		if (lengthZ >= lengthX && lengthZ >= lengthY) {
			longestAxisLength = lengthZ;
			longestAxis = Z;	// Z
		}

		//float bestSplitPosition = findBestSplitPosition();

		//LOG_DEBUG("best split at: " << bestSplitPosition)

		float longestAxisSplit;
		switch (longestAxis) {
		case X:
			longestAxisSplit = (boundingBox.min.x + boundingBox.max.x) / 2;
			//longestAxisSplit = boundingBox.min.x + (longestAxisLength * bestSplitPosition);
			break;
		case Y:
			longestAxisSplit = (boundingBox.min.y + boundingBox.max.y) / 2;
			//longestAxisSplit = boundingBox.min.y + (longestAxisLength * bestSplitPosition);
			break;
		case Z:
			longestAxisSplit = (boundingBox.min.z + boundingBox.max.z) / 2;
			//longestAxisSplit = boundingBox.min.z + (longestAxisLength * bestSplitPosition);
			break;
		default:
			break;
		}

		while (primitives.size() > 0) {
			bool lower = false;
			bool equal = false;
			Primitive* primitive = primitives.back();
			primitives.pop_back();

			BBox primitiveBox = primitive->getBounds();
			float boxMiddleX;
			float boxMiddleY;
			float boxMiddleZ;

			switch (longestAxis) {
			case X:
				boxMiddleX = (primitiveBox.max.x + primitiveBox.min.x) / 2;
				equal = boxMiddleX == longestAxisSplit;
				//equal = ((boxMiddleX - boundingBox.min.x) / longestAxisLength) == bestSplitPosition;
				//LOG_DEBUG("X: " << boxMiddleX << " < " << longestAxisSplit)
				//lower = ((boxMiddleX - boundingBox.min.x) / longestAxisLength) < bestSplitPosition;
				lower = boxMiddleX < longestAxisSplit;
				break;
			case Y:
				boxMiddleY = (primitiveBox.max.y + primitiveBox.min.y) / 2;
				equal = boxMiddleY == longestAxisSplit;
				//equal = ((boxMiddleY - boundingBox.min.y) / longestAxisLength) == bestSplitPosition;
				//LOG_DEBUG("Y: " << boxMiddleY << " < " << longestAxisSplit)
				lower = boxMiddleY < longestAxisSplit;
				//lower = ((boxMiddleY - boundingBox.min.y) / longestAxisLength) < bestSplitPosition;
				break;
			case Z:
				boxMiddleZ = (primitiveBox.max.z + primitiveBox.min.z) / 2;
				equal = boxMiddleZ == longestAxisSplit;
				//equal = ((boxMiddleZ - boundingBox.min.z) / longestAxisLength) == bestSplitPosition;
				//LOG_DEBUG("Z: " << boxMiddleZ << " < " << longestAxisSplit)
				//lower = ((boxMiddleZ - boundingBox.min.z) / longestAxisLength) < bestSplitPosition;
				lower = boxMiddleZ < longestAxisSplit;
				break;
			default:
				break;
			}
			//LOG_DEBUG("bestSplitPosition = " << bestSplitPosition)
			if (equal) {
				if (leftChild == nullptr) {
					leftChild = new BVH();
				}
				if (rightChild == nullptr) {
					rightChild = new BVH();
				}
				if (leftChild->primitives.size() < rightChild->primitives.size()) {
					//LOG_DEBUG("equal put to left")
					leftChild->add(primitive);
				} else {
					//LOG_DEBUG("equal put to right")
					rightChild->add(primitive);
				}
			} else {
				if (lower) {
					if (leftChild == nullptr) {
						leftChild = new BVH();
					}
					//LOG_DEBUG("put to left")
					leftChild->add(primitive);
				} else {
					if (rightChild == nullptr) {
						rightChild = new BVH();
					}
					//LOG_DEBUG("put to right")
					rightChild->add(primitive);
				}
			}
		}
	}
	if (leftChild != nullptr) {
		leftChild->rebuildIndex();
	}
	if (rightChild != nullptr) {
		rightChild->rebuildIndex();
	}

}

float BVH::findBestSplitPosition() {
	float bins[BIN_COUNT];
	int elementCount[BIN_COUNT];
	for (int i = 0; i < BIN_COUNT; i++) {
		bins[i] = 0;
		elementCount[i] = 0;
	}
	for (int i = 0; i < primitives.size(); i++) {
		BBox primitiveBox = primitives[i]->getBounds();
		float boxMiddleX;
		float boxMiddleY;
		float boxMiddleZ;
		int binNumber;
		switch (longestAxis) {
		case X:
			//boxMiddleX = (primitiveBox.max.x + primitiveBox.min.x) / 2;
			boxMiddleX = primitives[i]->getCenterPoint().x;
			binNumber = roundf(((boxMiddleX - boundingBox.min.x) / longestAxisLength) * (BIN_COUNT - 1));
			//LOG_DEBUG("put to bin number: " << binNumber)
			bins[binNumber] += primitiveBox.getArea();
			break;
		case Y:
			//boxMiddleY = (primitiveBox.max.y + primitiveBox.min.y) / 2;
			boxMiddleY = primitives[i]->getCenterPoint().y;
			binNumber = roundf(((boxMiddleY - boundingBox.min.y) / longestAxisLength) * (BIN_COUNT - 1));
			//LOG_DEBUG("put to bin number: " << binNumber)
			bins[binNumber] += primitiveBox.getArea();
			break;
		case Z:
			//boxMiddleZ = (primitiveBox.max.z + primitiveBox.min.z) / 2;
			boxMiddleZ = primitives[i]->getCenterPoint().z;
			binNumber = roundf(((boxMiddleZ - boundingBox.min.z) / longestAxisLength) * (BIN_COUNT - 1));
			//LOG_DEBUG("put to bin number: " << binNumber)
			bins[binNumber] += primitiveBox.getArea();
			break;
		default:
			break;
		}
		elementCount[binNumber]++;
	}
	float bestSplit = 0;
	float bestResult = FLT_MAX;
	for (int i = 1; i < BIN_COUNT; i++) {
		float surfaceAreaLeft = 0;
		int elementCountLeft = 0;
		for (int j = 0; j < i; j++) {
			surfaceAreaLeft += bins[j];
			elementCountLeft += elementCount[j];
		}
		float leftSplit = (surfaceAreaLeft / totalArea) * elementCountLeft;
		float rightSplit = ((totalArea - surfaceAreaLeft) / totalArea) * (primitives.size() - elementCountLeft);
		if ((leftSplit + rightSplit) < bestResult) {
			bestSplit = i;
			bestResult = leftSplit + rightSplit;
			LOG_DEBUG("better split at " << bestSplit)
			LOG_DEBUG(
					"elementCountLeft " << elementCountLeft << " total: " << primitives.size() << " result: " << (leftSplit + rightSplit))
		}
	}
	LOG_DEBUG("best split" << bestSplit)
	return (bestSplit / BIN_COUNT);
}

BVH::~BVH() {

}

void BVH::add(Primitive* p) {
	primitives.push_back(p);
	boundingBox.extend(p->getBounds());
	totalArea += p->getBounds().getArea();
}

void BVH::setMaterial(Material* m) {
	for (int i = 0; i < primitives.size(); i++) {
		primitives[i]->setMaterial(m);
	}
}

void BVH::setCoordMapper(CoordMapper* cm) {

}

Point BVH::getCenterPoint() {
	return Point(boundingBox.max.x - boundingBox.min.x, boundingBox.max.y - boundingBox.min.y, boundingBox.max.z - boundingBox.min.z);
}

}


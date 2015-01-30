/*
 * motionblur.cpp
 *
 *  Created on: 09.01.2015
 *      Author: chris
 */

#include <rt/primmod/motionblur.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/point.h>
#include <rt/primmod/instance.h>
#include <core/matrix.h>

#include <core/random.h>
#include <math.h>
#include <rt/ray.h>

namespace rt {

MotionBlur::MotionBlur(Primitive* primitive, Vector movementDirection, float timeInterval) :
		primitive(primitive), movementDirection(movementDirection), timeInterval(timeInterval) {
}

BBox MotionBlur::getBounds() const {
	return primitive->getBounds();
}

Intersection MotionBlur::intersect(const Ray& ray, float previousBestDistance) const {
	Vector blurDirection = movementDirection * random(timeInterval);
	Ray blurredRay(ray.o, (ray.d + blurDirection).normalize());
	Intersection intersection = primitive->intersect(blurredRay, previousBestDistance);
	if (intersection) {
		intersection.ray = ray;
	}
	return intersection;

}

void MotionBlur::setMaterial(Material* m) {
	primitive->setMaterial(m);
}

void MotionBlur::setCoordMapper(CoordMapper* cm) {
	primitive->setCoordMapper(cm);
}

Point MotionBlur::getCenterPoint() {
	primitive->getCenterPoint();
}

}


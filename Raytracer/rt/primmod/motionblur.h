/*
 * motionblur.h
 *
 *  Created on: 09.01.2015
 *      Author: chris
 */

#ifndef RT_MATERIALS_MOTIONBLUR_H_
#define RT_MATERIALS_MOTIONBLUR_H_

#include <rt/primitive.h>
#include <rt/intersection.h>
#include <rt/bbox.h>

namespace rt {

class MotionBlur: public Primitive {
public:
	Primitive* primitive;
	Vector movementDirection;
	float timeInterval;

	MotionBlur(Primitive* primitve, Vector movementDirection, float timeInterval);
	virtual BBox getBounds() const;
	virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
	virtual void setMaterial(Material* m);
	virtual void setCoordMapper(CoordMapper* cm);
	virtual Point getCenterPoint();
};

}

#endif /* RT_MATERIALS_MOTIONBLUR_H_ */

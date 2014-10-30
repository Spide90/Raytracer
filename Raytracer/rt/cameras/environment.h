/*
 * Environment.h
 *
 *  Created on: 30.10.2014
 *      Author: chris
 */

#ifndef RT_CAMERAS_ENVIRONMENT_H_
#define RT_CAMERAS_ENVIRONMENT_H_

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

class EnvironmentCamera: public Camera {
public:
	Point center;
	Vector forward;
	Vector up;
	Vector imageX;
	Vector imageY;
	float horizontalAngle;
	float verticalAngle;
	float aspectRatio;

	EnvironmentCamera(const Point& center, const Vector& forward, const Vector& up, float horizontalAngle, float verticalAngle,
			float aspectRatio);

	virtual Ray getPrimaryRay(float x, float y) const;
};

}



#endif /* RT_CAMERAS_ENVIRONMENT_H_ */

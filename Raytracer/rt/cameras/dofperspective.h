#ifndef CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

class DOFPerspectiveCamera : public Camera {
public:
	Point center;
	Vector forward;
	Vector up;
	Vector imageX;
	Vector imageY;
	float verticalOpeningAngle;
	float horizontalOpeningAngle;
	float focalDistance;
	float apertureRadius;

    DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
        );

    virtual Ray getPrimaryRay(float x, float y) const;

};

}


#endif

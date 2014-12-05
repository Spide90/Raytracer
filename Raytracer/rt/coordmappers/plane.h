#ifndef CG1RAYTRACER_COORDMAPPERS_PLANE_HEADER
#define CG1RAYTRACER_COORDMAPPERS_PLANE_HEADER

#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>

namespace rt {

class Intersection;

class PlaneCoordMapper : public CoordMapper{
public:
	Vector e1, e2;
    PlaneCoordMapper(const Vector& e1, const Vector& e2);
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif

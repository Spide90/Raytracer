#ifndef CG1RAYTRACER_SOLIDS_QUADRICS_HEADER
#define CG1RAYTRACER_SOLIDS_QUADRICS_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>

namespace rt {

class Quadric : public Solid {
public:
	float a,b,c,d,e,f,g,h,i,j;

    Quadric() {}
    Quadric(const float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
    virtual float getArea() const;
};

}


#endif

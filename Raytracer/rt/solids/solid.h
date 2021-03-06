#ifndef CG1RAYTRACER_SOLIDS_SOLID_HEADER
#define CG1RAYTRACER_SOLIDS_SOLID_HEADER

#include <rt/primitive.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/coordmappers/world.h>

namespace rt {

class Material;
//class CoordMapper;

/*
A solid is a physical primitive that has material and can be textured
*/
class Solid : public Primitive {
public:
    Material* material;
    CoordMapper* texMapper;
    bool isFracLand = false;

    explicit Solid(CoordMapper* texMapper = nullptr, Material* material = nullptr);
	virtual Point sample() const = 0;
    virtual float getArea() const = 0;
    virtual void setMaterial(Material* m) { material = m; }
    virtual void setCoordMapper(CoordMapper* cm) { texMapper = cm; }
    virtual Point getCenterPoint() = 0;
};

}


#endif

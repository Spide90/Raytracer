#include <rt/primitive.h>
#include <rt/primmod/instance.h>
#include <rt/bbox.h>
#include <rt/intersection.h>

namespace rt {

    Instance::Instance(Primitive* content){}

    void Instance::reset(){} //reset transformation back to identity
    void Instance::translate(const Vector& t){}
    void Instance::rotate(const Vector& axis, float angle){}
    void Instance::scale(float scale){}
    void Instance::scale(const Vector& scale){}

    BBox Instance::getBounds()const{
    	return BBox();
    }
    Intersection Instance::intersect(const Ray& ray, float previousBestDistance)const{
    	return Intersection();
    }
    void Instance::setMaterial(Material* m){}
    void Instance::setCoordMapper(CoordMapper* cm){}

}

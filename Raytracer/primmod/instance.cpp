#include <rt/primitive.h>
#include <primmod/instance.h>

namespace rt {

    Instance::Instance(Primitive* content){}

    void Instance::reset(){} //reset transformation back to identity
    void Instance::translate(const Vector& t){}
    void Instance::rotate(const Vector& axis, float angle){}
    void Instance::scale(float scale){}
    void Instance::scale(const Vector& scale){}

    BBox Instance::getBounds()const{}
    Intersection Instance::intersect(const Ray& ray, float previousBestDistance=FLT_MAX)const{}
    void Instance::setMaterial(Material* m){}
    void Instance::setCoordMapper(CoordMapper* cm){}

}


#endif

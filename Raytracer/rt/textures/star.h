#ifndef CG1RAYTRACER_TEXTURES_STAR_HEADER
#define CG1RAYTRACER_TEXTURES_STAR_HEADER

#include <core/vector.h>

#include <rt/textures/texture.h>
#include <core/color.h>

namespace rt {

class StarTexture : public Texture {
public:
    StarTexture();
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord);
    virtual RGBColor getColorDY(const Point& coord);
};

}

#endif

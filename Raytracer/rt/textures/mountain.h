#ifndef CG1RAYTRACER_TEXTURES_MOUNTAIN_HEADER
#define CG1RAYTRACER_TEXTURES_MOUNTAIN_HEADER

#include <core/vector.h>

#include <rt/textures/texture.h>
#include <core/color.h>

namespace rt {

class MountainTexture : public Texture {
public:
	RGBColor color;

    MountainTexture();
    MountainTexture(const RGBColor& color);
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord);
    virtual RGBColor getColorDY(const Point& coord);
};

}

#endif

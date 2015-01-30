#ifndef CG1RAYTRACER_TEXTURES_MOUNTAIN_HEADER
#define CG1RAYTRACER_TEXTURES_MOUNTAIN_HEADER

#include <core/vector.h>
#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/image.h>

namespace rt {

class MountainTexture: public Texture {
public:
	enum BorderHandlingTypeMountain {
		CLAMP, MIRROR, REPEAT
	};

	enum InterpolationTypeMountain {
		NEAREST, BILINEAR
	};

	BorderHandlingTypeMountain snow_bh;
	InterpolationTypeMountain snow_i;
	Image snow_image;

	RGBColor color;

	MountainTexture();
	MountainTexture(const RGBColor& color, const Image& snow_image, BorderHandlingTypeMountain snow_bh = REPEAT,
			InterpolationTypeMountain snow_i = BILINEAR);
	MountainTexture(const RGBColor& color, const std::string& snow_filename, BorderHandlingTypeMountain snow_bh = REPEAT,
			InterpolationTypeMountain snow_i = BILINEAR);
	virtual RGBColor getColor(const Point& coord);
	virtual RGBColor getColorDX(const Point& coord);
	virtual RGBColor getColorDY(const Point& coord);
	virtual RGBColor ImageGetColor(const Image& image, BorderHandlingTypeMountain bh,
			InterpolationTypeMountain i, const Point& coord);
};

}

#endif

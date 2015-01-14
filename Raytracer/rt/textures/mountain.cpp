#include <core/vector.h>

#include <rt/textures/mountain.h>
#include <rt/textures/texture.h>
#include <core/point.h>
#include <core/color.h>

namespace rt {

MountainTexture::MountainTexture() {
	color = RGBColor(139.f / 255.f, 69.f / 255.f, 19.f / 255.f);
}

MountainTexture::MountainTexture(const RGBColor& color) :
		color(color) {
}

RGBColor MountainTexture::getColor(const Point& coord) {
	if(coord.y > 80.f){
		RGBColor ret = ((coord.y - 80.f) / 15.f * RGBColor(1.f, 1.f, 1.f) + color).clamp();
		return ret;
	}
	else{
		if(coord.y < 60.f){
			float frac = (std::max(coord.y - 40.f, 0.f) / 20.f);
			RGBColor ret = frac * color + (1 - frac) * RGBColor(0.f, 100.f / 255.f, 0.f);
			return ret;
		}
		else{
			return color;
		}
	}

}

RGBColor MountainTexture::getColorDX(const Point& coord) {
	// TODO
	return RGBColor(0, 0, 0);
}

RGBColor MountainTexture::getColorDY(const Point& coord) {
	// TODO
	return RGBColor(0, 0, 0);
}

}

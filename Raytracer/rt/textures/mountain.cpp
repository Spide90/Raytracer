#include <core/vector.h>

#include <rt/textures/mountain.h>
#include <rt/textures/texture.h>
#include <core/point.h>
#include <core/color.h>
#include <core/image.h>
#include <core/interpolate.h>
#include <math.h>

namespace rt {

MountainTexture::MountainTexture() {
	color = RGBColor(139.f / 255.f, 69.f / 255.f, 19.f / 255.f);
	snow_bh = CLAMP;
	snow_i = NEAREST;
}

MountainTexture::MountainTexture(const RGBColor& color, const Image& snow_image, BorderHandlingTypeMountain snow_bh,
		InterpolationTypeMountain snow_i) : color(color), snow_image(snow_image), snow_bh(snow_bh), snow_i(snow_i){

}
MountainTexture::MountainTexture(const RGBColor& color, const std::string& snow_filename, BorderHandlingTypeMountain snow_bh,
		InterpolationTypeMountain snow_i) : color(color), snow_bh(snow_bh), snow_i(snow_i){
	//snow_image.readPNG(snow_filename);
}

RGBColor MountainTexture::getColor(const Point& coord) {
//	if(coord.y > 95.f){
//		return ImageGetColor(snow_image, snow_bh, snow_i, coord);
//	}
	if(coord.y > 80.f){
		RGBColor ret = (((coord.y - 80.f) / 15.f) * RGBColor(1.f, 1.f, 1.f) + color).clamp();
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
	return RGBColor(0, 0, 0);
}

RGBColor MountainTexture::getColorDY(const Point& coord) {
	return RGBColor(0, 0, 0);
}

RGBColor MountainTexture::ImageGetColor(const Image& image, BorderHandlingTypeMountain bh,
		InterpolationTypeMountain i, const Point& coord){
	float tu, tv, fl_x, fl_y, xW, yW;
	unsigned int ctu, ctv, ftu, ftv;
	RGBColor color;
	const float EPSILON = 1 / image.width();
	const float DELTA = 1 / image.height();

	switch (bh) {
	case REPEAT:
		tu = (coord.x - floorf(coord.x)) * image.width();
		tv = (coord.y - floorf(coord.y)) * image.height();
		switch (i) {
		case NEAREST:
			tu = roundf(tu) == image.width() ? 0 : roundf(tu);
			tv = roundf(tv) == image.height() ? 0 : roundf(tv);
			return image(tu, tv);
			break;
		case BILINEAR:
			ctu = ceilf(tu) == image.width() ? 0 : ceilf(tu);
			ctv = ceilf(tv) == image.height() ? 0 : ceilf(tv);
			ftu = floorf(tu);
			ftv = floorf(tv);
			xW = tu - floorf(tu);
			yW = tv - floorf(tv);
			color = lerp2d(image(ftu, ftv), image(ctu, ftv), image(ftu, ctv),
					image(ctu, ctv), xW, yW);
			return color;
			break;
		default:
			break;
		}
		break;
	case CLAMP:
		if (coord.x >= 0) {
			tu = coord.x * image.width() >= image.width() ?
					(image.width() - 1) : coord.x * image.width();
		} else {
			tu = 0;
		}
		if (coord.y >= 0) {
			tv = coord.y * image.height() >= image.height() ?
					(image.height() - 1) : coord.y * image.height();
		} else {
			tv = 0;
		}
		switch (i) {
		case NEAREST:
			//correct!
			tu = roundf(tu) == image.width() ? (image.width() - 1) : roundf(tu);
			tv = roundf(tv) == image.height() ?
					(image.height() - 1) : roundf(tv);
			return image(tu, tv);
			break;
		case BILINEAR:
			ctu = ceilf(tu) == image.width() ? (image.width() - 1) : ceilf(tu);
			ctv = ceilf(tv) == image.height() ?
					(image.height() - 1) : ceilf(tv);
			ftu = floorf(tu);
			ftv = floorf(tv);
			xW = tu - floorf(tu);
			yW = tv - floorf(tv);
			color = lerp2d(image(ftu, ftv), image(ctu, ftv), image(ftu, ctv),
					image(ctu, ctv), xW, yW);
			return color;
			break;
		default:
			break;
		}
		break;
	case MIRROR:
		if ((int) floorf(coord.x) % 2) {
			tu = (ceilf(coord.x) - coord.x) * (image.width() - 1);
		} else {
			tu = (coord.x - floor(coord.x)) * (image.width() - 1);
		}

		if ((int) floorf(coord.y) % 2) {
			tv = (ceilf(coord.y) - coord.y) * (image.height() - 1);
		} else {
			tv = (coord.y - floor(coord.y)) * (image.height() - 1);
		}

		//		if ((int) floorf(coord.x) % 2) {
		//			tu = (ceilf(coord.x) - coord.x);
		//		} else {
		//			tu = (coord.x - floor(coord.x));
		//		}
		//
		//		if ((int) floorf(coord.y) % 2) {
		//			tv = (ceilf(coord.y) - coord.y);
		//		} else {
		//			tv = (coord.y - floor(coord.y));
		//		}

		switch (i) {
		case NEAREST:
			//				tu = roundf(tu * image.width()) == image.width() ?
			//						(image.width() - 1) : roundf(tu * image.width());
			//				tv = roundf(tv * image.height()) == image.height() ?
			//						(image.height() - 1) : roundf(tv * image.height());
			//				return image(tu, tv);
			//				break;
			tu = roundf(tu) == image.width() ? (image.width() - 1) : roundf(tu);
			tv = roundf(tv) == image.height() ?
					(image.height() - 1) : roundf(tv);
			return image(tu, tv);
			break;
		case BILINEAR:
			ctu = (unsigned int) ceilf(tu);
			ctv = (unsigned int) ceilf(tv);
			ftu = (unsigned int) floorf(tu);
			ftv = (unsigned int) floorf(tv);

			//			if(ctu == image.width() && ctv == image.height()){
			//			}

			xW = (tu - floorf(tu));
			yW = (tv - floorf(tv));

			color = lerp2d(image(ftu, ftv), image(ctu, ftv), image(ftu, ctv),
					image(ctu, ctv), xW, yW);
			return color;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

}
}

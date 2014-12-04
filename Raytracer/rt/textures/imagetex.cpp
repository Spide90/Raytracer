/*
 * imagetex.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/textures/imagetex.h>
#include <core/vector.h>
#include <core/image.h>
#include <core/point.h>
#include <rt/textures/texture.h>
#include <math.h>
#include <core/interpolate.h>

namespace rt {

ImageTexture::ImageTexture() {
	bh = CLAMP;
	i = NEAREST;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i) :
		image(image), bh(bh), i(i) {
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i) :
		bh(bh), i(i) {
	image.readPNG(filename);
}

RGBColor ImageTexture::getColor(const Point& coord) {
	float tu, tv, fl_x, fl_y;
	float ctu, ctv, xW, yW, ftu, ftv;
	RGBColor color;
	switch (bh) {
	case REPEAT:
		if (coord.x >= 0) {
			tu = coord.x * image.width() >= image.width() ?
					(int) (coord.x * image.width()) % image.width() : coord.x * image.width();
		} else {
			tu = (int) (coord.x * image.width()) % image.width();
		}

		if (coord.y >= 0) {
			tv = coord.y * image.height() >= image.height() ?
					(int) (coord.y * image.height()) % image.height() : coord.y * image.height();
		} else {
			tv = (int) (coord.y * image.height()) % image.height();
		}
		switch (i) {
		case NEAREST:
			tu = roundf(tu) == image.width() ? 0 : roundf(tu);
			tv = roundf(tv) == image.height() ? 0 : roundf(tv);
			//LOG_DEBUG("nearest: " << tu << ", " << tv);
			return image(tu, tv);
			break;
		case BILINEAR:
			ctu = ceilf(tu) == image.width() ? 0 : ceilf(tu);
			ctv = ceilf(tv) == image.height() ? 0 : ceilf(tv);
			ftu = floorf(tu) == 0 ? ceilf(tu) : floorf(tu);
			ftv = floorf(tv) == 0 ? ceilf(tv) : floorf(tv);
			xW = tu - floorf(tu);
			yW = tv - floorf(tv);
			color = lerp2d(image(ftu, ftv), image(ctu, ftv), image(ftu, ctv), image(ctu, ctv), xW, yW);
			return color;
			break;
		default:
			break;
		}
		break;
	case CLAMP:
		if (coord.x >= 0) {
			tu = coord.x * image.width() >= image.width() ? image.width() - 1 : coord.x * image.width();
		} else {
			tu = 0;
		}
		if (coord.y >= 0) {
			tv = coord.y * image.height() >= image.height() ? image.height() - 1 : coord.y * image.height();
		} else {
			tv = 0;
		}
		switch (i) {
		case NEAREST:
			//correct!
			tu = roundf(tu) == image.width() ? image.width() - 1 : roundf(tu);
			tv = roundf(tv) == image.height() ? image.height() - 1 : roundf(tv);
			return image(tu, tv);
			break;
		case BILINEAR:
			ctu = ceilf(tu) == image.width() ? 0 : ceilf(tu);
			ctv = ceilf(tv) == image.height() ? 0 : ceilf(tv);
			ftu = floorf(tu) == 0 ? ceilf(tu) : floorf(tu);
			ftv = floorf(tv) == 0 ? ceilf(tv) : floorf(tv);
			xW = tu - floorf(tu);
			yW = tv - floorf(tv);
			color = lerp2d(image(ftu, ftv), image(ctu, ftv), image(ftu, ctv), image(ctu, ctv), xW, yW);
			return color;
			break;
		default:
			break;
		}
		break;
	case MIRROR:
		fl_x = fabs(coord.x);
		fl_y = fabs(coord.y);

		tu = fl_x >= 1 ? (ceilf(fl_x) - fl_x) : fl_x * image.width();
		tv = fl_y >= 1 ? ((ceilf(fl_y) - fl_y) * image.height()) : fl_y * image.height();
		switch (i) {
		case NEAREST:
			tu = roundf(tu) == image.width() ? image.width() - 1 : roundf(tu);
			tv = roundf(tv) == image.height() ? image.height() - 1 : roundf(tv);
			return image(tu, tv);
			break;
		case BILINEAR:
			ctu = ceilf(tu) == image.width() ? image.width() - 1 : ceilf(tu);
			ctv = ceilf(tv) == image.height() ? image.height() - 1 : ceilf(tv);
			ftu = floorf(tu);
			ftv = floorf(tv);
			xW = tu - floorf(tu);
			yW = tv - floorf(tv);
			color = lerp2d(image(ftu, ftv), image(ctu, ftv), image(ftu, ctv), image(ctu, ctv), xW, yW);
			return color;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return image(tu, tv);
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
	return RGBColor(0, 0, 0);
}
RGBColor ImageTexture::getColorDY(const Point& coord) {
	return RGBColor(0, 0, 0);
}

}


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
	float tu, tv, fl_x, fl_y, xW, yW;
	unsigned int ctu, ctv, ftu, ftv;
	RGBColor color;
	const float EPSILON = 1 / image.width();
	const float DELTA = 1 / image.height();

	switch (bh) {
	case REPEAT:
//		if (coord.x >= 0) {
////			tu = coord.x * image.width() >= image.width() ?
////					(int) (coord.x * image.width()) % image.width() : coord.x * image.width();
//			tu = coord.x * image.width() >= image.width() ?
//					(coord.x - floorf(coord.x)) * image.width() : coord.x * image.width();
//		} else {
////			tu = (int) (coord.x * image.width()) % image.width();
//			tu = (coord.x - floorf(coord.x)) * image.width();
//		}

		tu = (coord.x - floorf(coord.x)) * image.width();
		tv = (coord.y - floorf(coord.y)) * image.height();

//		if (coord.y >= 0) {
//			tv = coord.y * image.height() >= image.height() ?
//					(int) (coord.y * image.height()) % image.height() : coord.y * image.height();
//		} else {
//			tv = (int) (coord.y * image.height()) % image.height();
//		}

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
			color = lerp2d(image(ftu, ftv), image(ctu, ftv), image(ftu, ctv), image(ctu, ctv), xW, yW);
			return color;
			break;
		default:
			break;
		}
		break;
	case CLAMP:
		if (coord.x >= 0) {
			tu = coord.x * image.width() >= image.width() ? (image.width() - 1) : coord.x * image.width();
		} else {
			tu = 0;
		}
		if (coord.y >= 0) {
			tv = coord.y * image.height() >= image.height() ? (image.height() - 1) : coord.y * image.height();
		} else {
			tv = 0;
		}
		switch (i) {
		case NEAREST:
			//correct!
			tu = roundf(tu) == image.width() ? (image.width() - 1) : roundf(tu);
			tv = roundf(tv) == image.height() ? (image.height() - 1) : roundf(tv);
			return image(tu, tv);
			break;
		case BILINEAR:
			ctu = ceilf(tu) == image.width() ? (image.width() - 1) : ceilf(tu);
			ctv = ceilf(tv) == image.height() ? (image.height() - 1) : ceilf(tv);
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
			tv = roundf(tv) == image.height() ? (image.height() - 1) : roundf(tv);
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
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
//	uint width = image.width();
//
//	float derX = (coord.x + 1 / width)

//LOG_DEBUG("x: " << coord.x << ", y: " << coord.y;

//	float X = floorf(coord.x * image.width());
//	float upperX = ceilf(coord.x * image.width());
//	float Y = coord.y * image.height();
//	//LOG_DEBUG("lowerX " << lowerX << " upperX " << upperX);
//	//LOG_DEBUG("image width " << image.width() << " -1 " << image.width() - 1);
//	if(lowerX > 0.f){
//		lowerX--;
//	}
//	if(lowerX == upperX){
//		upperX++;
//	}
//	if (upperX == 0) {
//		return image(upperX, y);
//	}
//	if (lowerX >= image.width() - 1) {
//		return image(lowerX - 1, y);
//	}
//	RGBColor color = (image(upperX, y) - image(lowerX, y)) / 2.f;//lerp(image(lowerX, y), image(upperX, y), coord.x - lowerX);
//	float X = coord.x * image.width();
//	float Y = coord.y * image.height();
	return (this->getColor(Point(coord.x + (1.f / image.width()), coord.y, 0.f)) - this->getColor(Point(coord.x - (1.f / image.width()), coord.y, 0.f))) / 2.f;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
//	uint lowerY = floorf(coord.y * image.height());
//	uint upperY = ceilf(coord.y * image.height());
//	uint x = roundf(coord.x * (image.width() - 1));
	//LOG_DEBUG("lowerY " << lowerY << " upperY " << upperY);
	//LOG_DEBUG("image width " << image.width() << " -1 " << image.width() - 1);
//	if(lowerY > 0.f){
//		lowerY--;
//	}
//	if(lowerY == upperY){
//		upperY++;
//	}
//	if (upperY == 0) {
//		return image(x, upperY);
//	}
//	if (lowerY >= image.width() - 1) {
//		return image(x, lowerY - 1);
//	}
//	return (image(x, upperY) - image(x, lowerY)) / 2.f;//lerp(image(x, lowerY), image(x, lowerY), coord.y - lowerY);

//	float X = coord.x * image.width();
//	float Y = coord.y * image.height();
	return (this->getColor(Point(coord.x, coord.y + (1.f / image.height()), 0.f)) - this->getColor(Point(coord.x, coord.y - (1.f / image.height()), 0.f))) / 2.f;
}

}


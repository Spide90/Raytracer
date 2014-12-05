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

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh,
		InterpolationType i) :
		image(image), bh(bh), i(i) {
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh,
		InterpolationType i) :
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
					(int) (coord.x * image.width()) % image.width() :
					coord.x * image.width();
		} else {
			tu = (int) (coord.x * image.width()) % image.width();
		}

		if (coord.y >= 0) {
			tv = coord.y * image.height() >= image.height() ?
					(int) (coord.y * image.height()) % image.height() :
					coord.y * image.height();
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
			ftu = floorf(tu); // == 0 ? ceilf(tu) : floorf(tu);
			ftv = floorf(tv); // == 0 ? ceilf(tv) : floorf(tv);
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
			ftu = floorf(tu); //== 0 ? ceilf(tu) : floorf(tu);
			ftv = floorf(tv); //== 0 ? ceilf(tv) : floorf(tv);
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
//		fl_x = fabs((int) (coord.x / image.width()));
//		fl_y = fabs((int) (coord.y / image.height()));
//
//		LOG_DEBUG("coord.x = " << coord.x << " fl_x = " << fl_x);
//		LOG_DEBUG("coord.y = " << coord.y << " fl_y = " << fl_y);
//
//		if (coord.x >= 0) {
//			if ((int)fl_x % 2) {
//				tu = image.width() - (coord.x - image.width() * fl_x);
//			}
//			else{
//				tu = coord.x - image.width() * fl_x;
//			}
//		}
//		else{
//			if ((int)fl_x % 2) {
//				tu = -coord.x - image.width() * fl_x;
//			}
//			else{
//				tu = image.width() - (-coord.x - image.width() * fl_x);
//				LOG_DEBUG("tu = " << tu);
//			}
//		}
//
//		if (coord.y >= 0) {
//			if ((int)fl_y % 2) {
//				tv = image.height() - (coord.y - image.height() * fl_y);
//			}
//			else{
//				tv = coord.y - image.height() * fl_y;
//			}
//		}
//		else{
//			if ((int)fl_y % 2) {
//				tv = -coord.y - image.height() * fl_y;
//			}
//			else{
//				tv = image.height() - (-coord.y - image.height() * fl_y);
//			}
//		}

		//LOG_DEBUG("coord.x = " << coord.x << ", coord.y = " << coord.y);
		if (coord.x == floorf(coord.x) && (int) floorf(coord.x) % 2) {
			tu = image.width() - 1;
		}
		if (coord.x == floorf(coord.x) && !((int) floorf(coord.x) % 2)) {
			tu = 0;
		}
		if (coord.x != floorf(coord.x) && (int) floorf(coord.x) % 2) {
			tu = (ceilf(coord.x) - coord.x) * (image.width()-1);
		}
		if (coord.x != floorf(coord.x) && !((int) floorf(coord.x) % 2)) {
			tu = (coord.x - floor(coord.x)) * (image.width()-1);
		}

		if (coord.y == floorf(coord.y) && (int) floorf(coord.y) % 2) {
			tv = image.height() - 1;
		}
		if (coord.y == floorf(coord.y) && !((int) floorf(coord.y) % 2)) {
			tv = 0;
		}
		if (coord.y != floorf(coord.y) && (int) floorf(coord.y) % 2) {
			tv = (ceilf(coord.y) - coord.y) * (image.height()-1);
		}
		if (coord.y != floorf(coord.y) && !((int) floorf(coord.y) % 2)) {
			tv = (coord.y - floor(coord.y)) * (image.height()-1);
		}

		switch (i) {
		case NEAREST:
			tu = roundf(tu) == image.width() ? (image.width() - 1) : roundf(tu);
			tv = roundf(tv) == image.height() ?
					(image.height() - 1) : roundf(tv);
			return image(tu, tv);
			break;
		case BILINEAR:
//			if (ceilf(tu) == image.width()) {
//				ctu = image.width() - 2;
//				ftu = image.width() - 1;
//				xW = (tu - floorf(tu));
//			} else {
//				ctu = ceilf(tu);
//				ftu = floorf(tu);
//				xW = tu - floorf(tu);
//			}
//
//			if (ceilf(tv) == image.height()) {
//				ctv = image.height() - 2;
//				ftv = image.height() - 1;
//				yW = (tv - floorf(tv));
//			} else {
//				ctv = ceilf(tv);
//				ftv = floorf(tv);
//				yW = tv - floorf(tv);
//			}



//			if (ceilf(tu) == image.width()-1) {
//				ctu = image.width() - 2;
//				ftu = image.width() - 1;
//				xW = 1 - (tu - floorf(tu));
//			} else if (floorf(tu) == 0) {
//				ctu = 0;
//				ftu = 1;
//				xW = 1-(tu - floorf(tu));
//			} else {
//				ctu = ceilf(tu);
//				ftu = floorf(tu);
//				xW = tu - floorf(tu);
//			}
//
//			if (ceilf(tv) == image.height()-1) {
//				ctv = image.height() - 2;
//				ftv = image.height() - 1;
//				yW = 1-(tv - floorf(tv));
//			} else if (floorf(tv) == 0) {
//				ctv = 0;
//				ftv = 1;
//				yW = 1-(tv - floorf(tv));
//			} else {
//				ctv = ceilf(tv);
//				ftv = floorf(tv);
//				yW = tv - floorf(tv);
//			}

			ctu = ceilf(tu);
			ctv = ceilf(tv);
			ftu = floor(tu);
			ftv = floor(tv);

			xW = (int) floorf(coord.x) % 2 ? 1 - (tu - floorf(tu)) : (tu - floorf(tu));
			yW = (int) floorf(coord.x) % 2 ? 1 - (tv - floorf(tv)) : (tv - floorf(tv));
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

RGBColor ImageTexture::getColorDX(const Point& coord) {
	return RGBColor(0, 0, 0);
}
RGBColor ImageTexture::getColorDY(const Point& coord) {
	return RGBColor(0, 0, 0);
}

}


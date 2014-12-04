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

namespace rt {

ImageTexture::ImageTexture() {
	bh = CLAMP;
	i = NEAREST;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i): image(image), bh(bh), i(i){
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i): bh(bh), i(i) {
	image.readPNG(filename);
}

RGBColor ImageTexture::getColor(const Point& coord) {
	float tu, tv, fl_x, fl_y;
	switch (bh) {
		case REPEAT:
			if(coord.x >= 0){
				tu = coord.x * image.width() >= image.width() ? (int) (coord.x * image.width()) % image.width() : coord.x * image.width();
			}
			else{
				tu = (int) (coord.x * image.width()) % image.width();
			}

			if(coord.y >= 0){
				tv = coord.y * image.height() >= image.height() ? (int) (coord.y * image.height()) % image.height() : coord.y * image.height();
			}
			else{
				tv = (int) (coord.y * image.height()) % image.height();
			}

			break;

		case CLAMP:
			if(coord.x >= 0){
				tu = coord.x * image.width() >= image.width() ? image.width()-1 : coord.x * image.width();
			}
			else{
				tu = 0;
			}

			if(coord.y >= 0){
				tv = coord.y * image.height() >= image.height() ? image.height()-1 : coord.y * image.height();
			}
			else{
				tv = 0;
			}

			break;
		case MIRROR:
			fl_x = fabs(coord.x);
			fl_y = fabs(coord.y);

			tu = fl_x >= 1 ? (int)((1 - fl_x) * image.width()) % image.width() : fl_x * image.width();
			tv = fl_y >= 1 ? (int)((1 - fl_y) * image.height()) % image.height() : fl_y * image.height();

			break;
		default:
			break;
	}
	return image(tu, tv);

}

RGBColor ImageTexture::getColorDX(const Point& coord) {
	return RGBColor(0,0,0);
}
RGBColor ImageTexture::getColorDY(const Point& coord) {
	return RGBColor(0,0,0);
}

}


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
	float tu, tv;
	switch (bh) {
		case REPEAT:
			if(coord.x > 0){
				tu = coord.x * image.width() > image.width() ? (coord.x * image.width()) % image.width() : coord.x * image.width();
			}
			else{
				tu = (coord.x * image.width()) % image.width();
			}

			if(coord.y > 0){
				tv = coord.y * image.height() > image.height() ? (coord.y * image.height()) % image.height() : coord.y * image.height();
			}
			else{
				tv = (coord.y * image.height()) % image.height();
			}

			break;

		case CLAMP:
			if(coord.x > 0){
				tu = coord.x * image.width() > image.width() ? image.width() : coord.x * image.width();
			}
			else{
				tu = 0;
			}

			if(coord.y > 0){
				tv = coord.y * image.height() > image.height() ? image.height() : coord.y * image.height();
			}
			else{
				tv = 0;
			}

			break;
		case MIRROR:
			if(coord.x > 0){
				tu = coord.x * image.width() > image.width() ? image.width() : coord.x * image.width();
			}
			else{
				tu = 0;
			}

			if(coord.y > 0){
				tv = coord.y * image.height() > image.height() ? image.height() : coord.y * image.height();
			}
			else{
				tv = 0;
			}

			tu = coord.x - floor(coord.x);
			tv = coord.y - floor(coord.y);

			return image((unsigned int)(tu * image.width()), (unsigned int)(tv * image.height()));

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


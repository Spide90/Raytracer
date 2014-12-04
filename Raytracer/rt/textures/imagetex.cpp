/*
 * imagetex.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/textures/imagetex.h>
#include <core/vector.h>
#include <core/image.h>
#include <rt/textures/texture.h>

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

}

RGBColor ImageTexture::getColorDX(const Point& coord) {
	return RGBColor(0,0,0);
}
RGBColor ImageTexture::getColorDY(const Point& coord) {
	return RGBColor(0,0,0);
}

}


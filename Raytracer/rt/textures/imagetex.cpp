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

}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i) {

}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i) {

}

RGBColor ImageTexture::getColor(const Point& coord) {

}

RGBColor ImageTexture::getColorDX(const Point& coord) {

}

RGBColor ImageTexture::getColorDY(const Point& coord) {

}

}


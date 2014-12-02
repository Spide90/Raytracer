/*
 * checkerboard.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/textures/checkerboard.h>
#include <core/vector.h>
#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/point.h>
#include <math.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black):white(white), black(black) {
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
	int a;
	if(coord.x >= 0){
		a = (int)(coord.x * 2) % 2;
	}
	else{
		a = (int)(coord.x * (-2)) % 2;
		a = !a;
	}
	int b;
	if(coord.y >= 0){
		b = (int)(coord.y * 2) % 2;
	}
	else{
		b = (int)(coord.y * (-2)) % 2;
		b = !b;
	}
	int c;
	if(coord.z >= 0){
		c = (int)(coord.z * 2) % 2;
	}
	else{
		c = (int)(coord.z * (-2)) % 2;
		c = !c;
	}

	if((!c && a && !b) || (!c && !a && b) || (c && !a && !b) || (c && a && b)){
		return white;
	}
	else{
		return black;
	}
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
	return RGBColor(0,0,0);
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
	return RGBColor(0,0,0);
}

}


#include <core/vector.h>

#include <rt/textures/star.h>
#include <rt/textures/texture.h>
#include <core/point.h>
#include <core/color.h>

namespace rt {

StarTexture::StarTexture() {
}

float Starnoise(int x, int y, int z) {
	int n = x + y * 57 + z * 997;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}


RGBColor StarTexture::getColor(const Point& coord) {
	if(Starnoise(coord.x, coord.y, coord.z) > 0.995f){
		return RGBColor::rep(1000000000000.f);
	}
	else{
		return RGBColor::rep(0.f);
	}
}

RGBColor StarTexture::getColorDX(const Point& coord) {
	// TODO
	return RGBColor(0, 0, 0);
}

RGBColor StarTexture::getColorDY(const Point& coord) {
	// TODO
	return RGBColor(0, 0, 0);
}

}

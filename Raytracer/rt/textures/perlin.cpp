#include <rt/textures/perlin.h>
#include <core/point.h>
#include <core/scalar.h>
#include <core/color.h>
#include <math.h>
#include <core/interpolate.h>

namespace rt {

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black) :
		white(white), black(black) {
}

/* returns a value in range -1 to 1 */
float noise(int x, int y, int z) {
	int n = x + y * 57 + z * 997;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float smooth_noise(int x, int y, int z) {
	float corners = (noise(x - 1, y - 1, z - 1) + noise(x - 1, y - 1, z + 1) + noise(x - 1, y + 1, z - 1)
			+ noise(x - 1, y + 1, z + 1) + noise(x + 1, y - 1, z - 1) + noise(x + 1, y - 1, z + 1) + noise(x + 1, y + 1, z - 1)
			+ noise(x + 1, y + 1, z + 1)) / 64;
	float edgemiddle = (noise(x, y - 1, z - 1) + noise(x, y - 1, z + 1) + noise(x, y + 1, z - 1) + noise(x, y + 1, z + 1)
			+ noise(x + 1, y, z - 1) + noise(x + 1, y, z + 1) + noise(x - 1, y, z - 1) + noise(x - 1, y, z + 1)
			+ noise(x + 1, y - 1, z) + noise(x + 1, y + 1, z) + noise(x - 1, y - 1, z) + noise(x - 1, y + 1, z)) / 32;
	float adjacent = (noise(x, y, z - 1) + noise(x, y, z + 1) + noise(x, y - 1, z) + noise(x, y + 1, z) + noise(x - 1, y, z)
			+ noise(x + 1, y, z)) / 16;
	float center = noise(x, y, z) / 8;
	return (corners + edgemiddle + adjacent + center);
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
//	if(ampl.size() == 0){
//		ampl.push_back(1.f);
//		freq.push_back(frequency / 2);
//	}

	ampl.push_back(amplitude);
	freq.push_back(frequency);
}

RGBColor PerlinTexture::getColor(const Point& coord) {
	float interpol = 0;

//	interpol = interpol
//			+ 		fabs(lerp3d(noise(floor(coord.x * freq[0] / 2), floor(coord.y * freq[0] / 2), floor(coord.z * freq[0] / 2)), noise(floor(coord.x * freq[0] / 2) + 1, floor(coord.y * freq[0] / 2), floor(coord.z * freq[0] / 2)), noise(floor(coord.x * freq[0] / 2), floor(coord.y * freq[0] / 2) + 1, floor(coord.z * freq[0] / 2)),
//							noise(floor(coord.x * freq[0] / 2) + 1, floor(coord.y * freq[0] / 2) + 1, floor(coord.z * freq[0] / 2)), noise(floor(coord.x * freq[0] / 2), floor(coord.y * freq[0] / 2), floor(coord.z * freq[0] / 2) + 1),
//							noise(floor(coord.x * freq[0] / 2) + 1, floor(coord.y * freq[0] / 2), floor(coord.z * freq[0] / 2) + 1), noise(floor(coord.x * freq[0] / 2), floor(coord.y * freq[0] / 2) + 1, floor(coord.z * freq[0] / 2) + 1),
//							noise(floor(coord.x * freq[0] / 2) + 1, floor(coord.y * freq[0] / 2) + 1, floor(coord.z * freq[0] / 2) + 1), coord.x * freq[0] - floor(coord.x * freq[0] / 2), coord.y * freq[0] - floor(coord.y * freq[0] / 2), coord.z * freq[0] - floor(coord.z * freq[0] / 2)));

	for (int i = 0; i < ampl.size(); i++) {
		int int_x = floorf(coord.x * freq[i]);
		int int_y = floorf(coord.y * freq[i]);
		int int_z = floorf(coord.z * freq[i]);

		//interpol = interpol + fabs(noise(int_x, int_y, int_z) * ampl[i]);

		float frac_x = coord.x * freq[i] - int_x;
		float frac_y = coord.y * freq[i] - int_y;
		float frac_z = coord.z * freq[i] - int_z;

		//		interpol = interpol
//		 + 	 lerp3d(smooth_noise(int_x, int_y, int_z), smooth_noise(int_x + 1, int_y, int_z),
//		 smooth_noise(int_x, int_y + 1, int_z), smooth_noise(int_x + 1, int_y + 1, int_z),
//		 smooth_noise(int_x, int_y, int_z + 1), smooth_noise(int_x + 1, int_y, int_z + 1),
//		 smooth_noise(int_x, int_y + 1, int_z + 1), smooth_noise(int_x + 1, int_y + 1, int_z + 1), frac_x,
//		 frac_y, frac_z) * ampl[i];

		interpol = interpol
				+ lerp3d(noise(int_x, int_y, int_z), noise(int_x + 1, int_y, int_z), noise(int_x, int_y + 1, int_z),
						noise(int_x + 1, int_y + 1, int_z), noise(int_x, int_y, int_z + 1), noise(int_x + 1, int_y, int_z + 1),
						noise(int_x, int_y + 1, int_z + 1), noise(int_x + 1, int_y + 1, int_z + 1), frac_x, frac_y, frac_z)
						* ampl[i];

	}

	interpol = (interpol + 1) / 2;

	RGBColor color = lerp(black, white, interpol);
	return color;
}

RGBColor PerlinTexture::getColorDX(const Point& coord) {
	return RGBColor(0, 0, 0);
}
RGBColor PerlinTexture::getColorDY(const Point& coord) {
	return RGBColor(0, 0, 0);
}

}

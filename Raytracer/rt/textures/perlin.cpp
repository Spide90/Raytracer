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

void PerlinTexture::addOctave(float amplitude, float frequency) {
	ampl.push_back(amplitude);
	freq.push_back(frequency);
}

RGBColor PerlinTexture::getColor(const Point& coord) {
	float interpol = 0;

	for (int i = 0; i < ampl.size(); i++) {
		int int_x = floorf(coord.x * freq[i]);
		int int_y = floorf(coord.y * freq[i]);
		int int_z = floorf(coord.z * freq[i]);


		float frac_x = coord.x * freq[i] - int_x;
		float frac_y = coord.y * freq[i] - int_y;
		float frac_z = coord.z * freq[i] - int_z;

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

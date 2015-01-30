/*
 * heterogenious.h
 *
 *  Created on: 23.01.2015
 *      Author: chris
 */

#ifndef RT_VOLUME_HETEROGENIOUS_H_
#define RT_VOLUME_HETEROGENIOUS_H_

#include <rt/volume/fog.h>
#include <core/color.h>
#include <rt/textures/texture.h>
#include <rt/primitive.h>

namespace rt {

class HeterogeniousFog: public Fog {
public:

	Texture* fogTexture;
	Primitive* prim;
	float density;

	HeterogeniousFog(float density, Primitive* prim, Texture* fogTexture);

	virtual RGBColor getColor(Point hitPoint);

	virtual float transmittance(Point origin, Point hitPoint);

	virtual float getDensity(Point point);

	virtual Primitive* getPrimitive();
};

}



#endif /* RT_VOLUME_HETEROGENIOUS_H_ */

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
#include <rt/materials/material.h>

namespace rt {

class HeterogeniousFog: public Fog {
public:

	Material* fogMaterial;

	HeterogeniousFog(Material* material);

	virtual RGBColor getColor(Point hitPoint, Vector normal, Vector inDir, Vector outDir);

	virtual float transmittance(Point origin, Point hitPoint);

	virtual float getDensity(Point point);

};

}



#endif /* RT_VOLUME_HETEROGENIOUS_H_ */

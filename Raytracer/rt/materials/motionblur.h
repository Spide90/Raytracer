/*
 * motionblur.h
 *
 *  Created on: 09.01.2015
 *      Author: chris
 */

#ifndef RT_MATERIALS_MOTIONBLUR_H_
#define RT_MATERIALS_MOTIONBLUR_H_

#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

class MotionBlurMaterial : public Material {
public:
	Texture* emission;
	Texture* diffuse;
	Vector movementDirection;

    MotionBlurMaterial(Texture* emission, Texture* diffuse, Vector movementDirection);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
};

}



#endif /* RT_MATERIALS_MOTIONBLUR_H_ */

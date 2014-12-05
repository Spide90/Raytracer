/*
 * solid.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/solids/solid.h>
#include <rt/primitive.h>
#include <rt/coordmappers/world.h>
#include <core/float4.h>

namespace rt {

Solid::Solid(CoordMapper* texMapper, Material* material) : texMapper(texMapper), material(material) {
	if(texMapper == nullptr)
		this->texMapper = new WorldMapper(Float4(1.f, 1.f, 1.f, 1.f));
}

}


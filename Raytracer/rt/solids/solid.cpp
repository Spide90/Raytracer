/*
 * solid.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/solids/solid.h>
#include <rt/primitive.h>

namespace rt {

Solid::Solid(CoordMapper* texMapper, Material* material) : texMapper(texMapper), material(material) {

}

}


#ifndef UTIL_HELPERSH
#define UTIL_HELPERSH

#include "vec3.h"

namespace canvas {

vec3 random_in_unit_sphere();
vec3 reflect(const vec3& v, const vec3& n);
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);

}

#endif

#ifndef UTIL_RAYH
#define UTIL_RAYH

#include "vec3.h"

namespace canvas {

class ray {
public:
  vec3 o; // origin
  vec3 d; // direction
public:
  ray() {}
  ray(const vec3& o, const vec3& d);
  vec3 point_at_parameter(float t) const;
};

}

#endif

#ifndef HITABLE_AABBH
#define HITABLE_AABBH

#include <algorithm>
#include "util/ray.h"

namespace canvas {

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class AABB {
public:
  vec3 _min;
  vec3 _max;
public:
  AABB() {}
  AABB(const vec3& a, const vec3& b) : _min(a), _max(b) {}
  bool hit(const ray& r, float t_min, float t_max) const {
    for(int i = 0; i < 3; i++) {
      float inv_d = 1.0 / r.d[i];
      // refactor with swap. t0 > t1 ? swap(t0, t1)..
      float t0 = (_min[i] - r.o[i]) * inv_d;
      float t1 = (_max[i] - r.o[i]) * inv_d;
      if(inv_d < 0.0) std::swap(t0, t1);
      t_min = t0 > t_min ? t0 : t_min;
      t_max = t1 > t_max ? t1 : t_max;
      if(t_max <= t_min) return false;
    }
    return true;
  }
};

}

#endif

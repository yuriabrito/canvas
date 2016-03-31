#ifndef LIGHT_LIGHTH
#define LIGHT_LIGHTH

#include "util/vec3.h"
#include "hitable/hitable.h"
#include "hitable/hitable_list.h"

namespace canvas {

class Light {
public:
public:
  Light() {}
  virtual vec3 getDirection(hit_record& rec) const = 0;
  virtual vec3 L(hit_record& rec) = 0; // incident radiance
  virtual bool inShadow(const ray& r, const HitableList& world) const = 0;
};

}

#endif

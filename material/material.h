#ifndef MATERIAL_MATERIALH
#define MATERIAL_MATERIALH

#include "util/vec3.h"
#include "util/ray.h"
#include "hitable/hitable.h"

namespace canvas {

class Material {
public:
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
  virtual bool transmit() const {
    return false;
  }
};

}

#endif

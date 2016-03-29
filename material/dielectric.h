#ifndef MATERIAL_DIELECTRICH
#define MATERIAL_DIELECTRICH

#include "material.h"

namespace canvas {

class Dielectric : public Material {
public:
  float ref_idx;
public:
  Dielectric(float ref_idx);
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
};

}

#endif

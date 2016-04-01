#ifndef MATERIAL_DIELECTRICH
#define MATERIAL_DIELECTRICH

#include "material.h"

namespace canvas {

class Dielectric : public Material {
public:
  float ref_idx;
  float transmissivity;
public:
  Dielectric(float ref_idx, float transmissivity);
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
  virtual bool transmit() const;
};

}

#endif

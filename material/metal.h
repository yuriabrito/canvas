#ifndef MATERIAL_METALH
#define MATERIAL_METALH

#include "util/vec3.h"
#include "util/ray.h"
#include "material.h"

namespace canvas {

class Metal : public Material {
public:
  vec3 albedo;
  float fuzziness;
public:
  Metal(const vec3& albedo, float fuzziness);
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
};

}

#endif

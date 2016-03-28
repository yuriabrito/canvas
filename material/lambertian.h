#ifndef MATERIAL_LAMBERTIANH
#define MATERIAL_LAMBERTIANH

#include "util/vec3.h"
#include "util/ray.h"
#include "material.h"

namespace canvas {

class Lambertian : public Material {
public:
  vec3 albedo;
public:
  Lambertian(const vec3& albedo);
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
};

}

#endif

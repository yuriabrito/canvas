#include <iostream>
#include <cmath>
#include "util/helpers.h"
#include "dielectric.h"

namespace canvas {

Dielectric::Dielectric(float ref_idx, float transmissivity) : ref_idx(ref_idx), transmissivity(transmissivity) {}

float schlick(float cosine, float ref_idx) {
  float r0 = (1.0 - ref_idx) / (1 + ref_idx);
  r0 *= r0;
  return r0 + (1.0 - r0) * pow(1.0 - cosine, 5);
}

bool Dielectric::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
  attenuation = vec3(1.0);
  vec3 outward_normal;
  float ni_over_nt;
  float cosine = r_in.d * rec.normal / r_in.d.length();

  if(r_in.d * rec.normal > 0.0001) {
    outward_normal = -rec.normal;
    ni_over_nt = ref_idx;
    cosine = sqrt(1.0 - (ref_idx * ref_idx) * (1.0 - cosine * cosine) );
  }
  else {
    outward_normal = rec.normal;
    ni_over_nt = 1.0 / ref_idx;
    cosine = -cosine;
  }

  float reflect_prob;
  vec3 refracted;
  vec3 reflected = reflect(r_in.d.hat(), rec.normal);

  if(refract(r_in.d, outward_normal, ni_over_nt, refracted)) {
    reflect_prob = schlick(cosine, ref_idx);
  }
  else {
    scattered = ray(rec.p, reflected);
    reflect_prob = 1.0;
  }

  if(drand48() < reflect_prob) {
    scattered = ray(rec.p, reflected);
  }
  else {
    scattered = ray(rec.p, refracted);
  }
  return true;
}

bool Dielectric::transmit() const {
  return (transmissivity < drand48() ? true : false);
}

}

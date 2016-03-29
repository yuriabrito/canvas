#include "util/helpers.h"
#include "metal.h"
#include <iostream>

namespace canvas {

Metal::Metal(const vec3& albedo, float fuzziness) : albedo(albedo), fuzziness(fuzziness) {}

bool Metal::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
  vec3 reflected = reflect(r_in.d.hat(), rec.normal);
  scattered = ray(rec.p, reflected + fuzziness * random_in_unit_sphere());
  attenuation = albedo;
  return (scattered.d * rec.normal) > 0.0f;
}

}

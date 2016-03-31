#ifndef LIGHT_POINTLIGHTH
#define LIGHT_POINTLIGHTH

#include "light.h"

namespace canvas {

class PointLight : public Light {
private:
  vec3 point;
  vec3 color;
  float ls;
public:
  PointLight();
  PointLight(const vec3& point, const vec3& color, float ls);
  virtual vec3 getDirection(hit_record& rec);
  virtual vec3 L(hit_record& rec);
};

}

#endif

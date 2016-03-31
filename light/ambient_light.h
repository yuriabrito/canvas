#ifndef LIGHT_AMBIENTLIGHTH
#define LIGHT_AMBIENTLIGHTH

#include "light.h"

namespace canvas {

class AmbientLight : public Light {
private:
  vec3 color;
  float ls;
public:
  AmbientLight();
  AmbientLight(const vec3& color, float ls);
  virtual vec3 getDirection(hit_record& rec) const;
  virtual vec3 L(hit_record& rec);
  virtual bool inShadow(const ray& r, const HitableList& world) const;
};

}

#endif

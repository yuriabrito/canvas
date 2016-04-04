#ifndef UTIL_SCENEH
#define UTIL_SCENEH

#include <vector>
#include "light/light.h"
#include "light/ambient_light.h"
#include "hitable/hitable.h"
#include "hitable/hitable_list.h"

namespace canvas {

class Scene {
public:
  HitableList* world;
  AmbientLight* ambient_light;
  std::vector<Light*> lights;
public:
  Scene() {}
  void build(); // tmp
  void setWorld(std::vector<Hitable*> v_hitable);
  void addHitable(Hitable* hitable);
  void setAmbientLight(AmbientLight* ambient_light);
  void addLight(Light* light);
  // void parse(std::string file);
};

}

#endif

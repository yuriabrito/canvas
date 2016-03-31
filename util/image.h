#ifndef UTIL_IMAGEH
#define UTIL_IMAGEH

#include <vector>
#include "vec3.h"

namespace canvas {

class Image {
public:
  std::vector< std::vector<vec3> > rgb;
  float width;
  float height;
public:
  Image(float width, float height);
  std::vector<vec3>& operator[](size_t index);
  void save();
};

}

#endif

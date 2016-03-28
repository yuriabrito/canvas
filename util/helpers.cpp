#include <iostream>
#include "helpers.h"

namespace canvas {

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
  } while(p * p >= 1.0);
  return p;
}

}

#include <cmath>
#include "tests/catch.hh"
#include "util/vec3.h"
#include "util/ray.h"

#define ERR 0.0001

namespace canvas {

TEST_CASE("ray operations") {
  vec3 o(1,2,3);
  vec3 d(4,5,6);
  ray r(o, d);

  SECTION("new instance") {
    REQUIRE(r.o == o);
    REQUIRE(r.d == d);
  }

  SECTION("point_at_parameter") {
    vec3 p = r.point_at_parameter(5.0);
    // 1,2,3 + 5 * 4,5,6 = 21,27,33
    REQUIRE(p == vec3(21,27,33));
  }
}

}

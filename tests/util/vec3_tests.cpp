#include <cmath>
#include "tests/catch.hh"
#include "util/vec3.h"

#define ERR 0.0001

namespace canvas {

TEST_CASE("testing") {
  Vec3 v(1,2,3);

  SECTION("section") {
    REQUIRE(fabs(1.0 - 1.0) <= ERR);
  }
}

}

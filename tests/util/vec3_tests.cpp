#include <cmath>
#include "tests/catch.hh"
#include "util/vec3.h"

#define ERR 0.0001

namespace canvas {

TEST_CASE("vec3 operations") {
  vec3 v1(1,2,3);
  vec3 v2(1,2,3);
  vec3 v3(3,6,9);
  vec3 v4(3,2,1);

  SECTION("equivalence") {
    REQUIRE(v1 == v2);
  }

  SECTION("operator []") {
    REQUIRE(fabs(v3[0] - 3.0f) <= ERR);
  }

  SECTION("positive") {
    REQUIRE(+v1 == v1);
  }

  SECTION("negative") {
    REQUIRE(-v1 == vec3(-1,-2,-3));
  }

  SECTION("sum") {
    REQUIRE(v1 + v1 == vec3(2,4,6));
  }

  SECTION("sum assignment") {
    v1 += vec3(1,1,1);
    REQUIRE(v1 == vec3(2,3,4));
  }

  SECTION("difference") {
    REQUIRE(v1 - vec3(1,1,1) == vec3(0,1,2));
  }

  SECTION("difference assignment") {
    v1 -= vec3(1,1,1);
    REQUIRE(v1 == vec3(0,1,2));
  }

  SECTION("dot product") {
    REQUIRE(v1 * v2 == 1 + 4 + 9);
  }

  SECTION("cross product") {
    REQUIRE((v1 ^ v1) == vec3(0));
    REQUIRE((v1 ^ v4) == vec3(-4,8,-4));
  }

  SECTION("% product") {
    REQUIRE(v1 % v1 == vec3(1,4,9));
  }

  SECTION("scalar product") {
    REQUIRE(v1 * 3 == vec3(3,6,9));
    REQUIRE(3 * v1 == vec3(3,6,9));
  }

  SECTION("scalar division") {
    REQUIRE(v3 / 3 == vec3(1,2,3));
  }

  SECTION("scalar division assignment") {
    v3 /= 3;
    REQUIRE(v3 == vec3(1,2,3));
  }

  SECTION("length") {
    REQUIRE(fabs(sqrt(1+4+9) - v1.length()) <= ERR);
  }

  SECTION("hat") {
    REQUIRE(v1.hat() == (v1 / v1.length()));
  }

  SECTION("normalize") {
    v1.normalize();
    REQUIRE(v1 == v2.hat());
  }
}

}

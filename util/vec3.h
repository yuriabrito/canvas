#ifndef UTIL_VEC3H
#define UTIL_VEC3H

namespace canvas {

class vec3 {
public:
  float v[3];
public:
  vec3() {}
  vec3(float a);
  vec3(float a, float b, float c);
  const float operator[](int i) const;
  float& operator[](int i);
  const vec3& operator+() const;
  const vec3 operator+(const vec3& a) const;
  vec3& operator+=(const vec3& a);
  const vec3 operator-() const;
  const vec3 operator-(const vec3& a) const;
  vec3& operator-=(const vec3& a);
  const bool operator==(const vec3& a) const;
  const float operator*(const vec3& a) const;
  vec3& operator*=(const float f);
  vec3& operator/=(const float f);
  const float length() const;
};

const vec3 operator*(const vec3& v, const float a);
const vec3 operator*(const float f, const vec3& v);
const vec3 operator/(const vec3& v, const float a);

}

#endif

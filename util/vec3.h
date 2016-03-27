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
  float operator[](int i) const;
  float& operator[](int i);
  const vec3& operator+() const;
  vec3 operator+(const vec3& a) const;
  vec3& operator+=(const vec3& a);
  vec3 operator-() const;
  vec3 operator-(const vec3& a) const;
  vec3& operator-=(const vec3& a);
  bool operator==(const vec3& a) const;
  float operator*(const vec3& a) const; // dot
  vec3 operator^(const vec3& a) const; // cross
  vec3& operator*=(const float f);
  vec3& operator/=(const float f);
  float length() const;
  vec3 hat() const;
  void normalize();
};

vec3 operator*(const vec3& v, const float a);
vec3 operator*(const float f, const vec3& v);
vec3 operator/(const vec3& v, const float a);

}

#endif

#include <cmath>
#include <cassert>
#include "vec3.h"

namespace canvas {

vec3::vec3(float a) {
  v[0] = v[1] = v[2] = a;
}

vec3::vec3(float a, float b, float c) {
  v[0] = a; v[1] = b; v[2] = c;
}

const float vec3::operator[](int i) const {
  assert(i >= 0 && i < 3);
  return v[i];
}

float& vec3::operator[](int i) {
  assert(i >= 0 && i < 3);
  return v[i];
}

const vec3& vec3::operator+() const {
  return *this;
}

const vec3 vec3::operator+(const vec3& a) const {
  return vec3(v[0] + a.v[0], v[1] + a.v[1], v[2] + a.v[2]);
}

vec3& vec3::operator+=(const vec3& a) {
  v[0] += a.v[0]; v[1] += a.v[1]; v[2] += a.v[2];
  return *this;
}

const vec3 vec3::operator-() const {
  return vec3(-v[0], -v[1], -v[2]);
}

const vec3 vec3::operator-(const vec3& a) const {
  return *this + -a;
}

vec3& vec3::operator-=(const vec3& a) {
  v[0] -= a.v[0]; v[1] -= a.v[1]; v[2] -= a.v[2];
  return *this;
}

const bool vec3::operator==(const vec3& a) const {
  float ERR = 0.001;
  return fabs(v[0] - a.v[0]) <= ERR && fabs(v[1] - a.v[1]) <= ERR && fabs(v[2] - a.v[2]) <= ERR;
}

const float vec3::operator*(const vec3& a) const {
  return v[0] * a.v[0] + v[1] * a.v[1] + v[2] * a.v[2];
}

vec3& vec3::operator*=(const float f) {
  v[0] *= f; v[1] *= f; v[2] *= f;
  return *this;
}

vec3& vec3::operator/=(const float f) {
  v[0] /= f; v[1] /= f; v[2] /= f;
  return *this;
}

const float vec3::length() const {
  return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

const vec3 operator*(const vec3& v, const float f) {
  return vec3(v.v[0] * f, v.v[1] * f, v.v[2] * f);
}

const vec3 operator*(const float f, const vec3& v) {
  return operator*(v, f);
}

const vec3 operator/(const vec3& v, const float f) {
  return vec3(v.v[0] / f, v.v[1] / f, v.v[2] / f);
}

}

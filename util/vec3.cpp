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

float vec3::operator[](int i) const {
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

vec3 vec3::operator+(const vec3& a) const {
  return vec3(v[0] + a.v[0], v[1] + a.v[1], v[2] + a.v[2]);
}

vec3& vec3::operator+=(const vec3& a) {
  v[0] += a.v[0]; v[1] += a.v[1]; v[2] += a.v[2];
  return *this;
}

vec3 vec3::operator-() const {
  return vec3(-v[0], -v[1], -v[2]);
}

vec3 vec3::operator-(const vec3& a) const {
  return *this + -a;
}

vec3& vec3::operator-=(const vec3& a) {
  v[0] -= a.v[0]; v[1] -= a.v[1]; v[2] -= a.v[2];
  return *this;
}

bool vec3::operator==(const vec3& a) const {
  float ERR = 0.001;
  return fabs(v[0] - a.v[0]) <= ERR && fabs(v[1] - a.v[1]) <= ERR && fabs(v[2] - a.v[2]) <= ERR;
}

vec3 vec3::operator%(const vec3& a) const {
  return vec3(v[0] * a.v[0], v[1] * a.v[1], v[2] * a.v[2]);
}

float vec3::operator*(const vec3& a) const {
  return v[0] * a.v[0] + v[1] * a.v[1] + v[2] * a.v[2];
}

vec3 vec3::operator^(const vec3& a) const {
  return vec3(v[1] * a.v[2] - v[2] * a.v[1],
      -(v[0] * a.v[2] - v[2] * a.v[0]),
      v[0] * a.v[1] - v[1] * a.v[0]);
}

vec3& vec3::operator*=(const float f) {
  v[0] *= f; v[1] *= f; v[2] *= f;
  return *this;
}

vec3& vec3::operator%=(const vec3& a) {
  v[0] *= a.v[0]; v[1] *= a.v[1]; v[2] *= a.v[2];
  return *this;
}

vec3& vec3::operator/=(const float f) {
  v[0] /= f; v[1] /= f; v[2] /= f;
  return *this;
}

float vec3::length() const {
  return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

vec3 vec3::hat() const {
  float l_inv = 1.0f / length();
  return *this * l_inv;
}

void vec3::normalize() {
  float l_inv = 1.0f / length();
  v[0] *= l_inv; v[1] *= l_inv; v[2] *= l_inv;
}

vec3 operator*(const vec3& v, const float f) {
  return vec3(v.v[0] * f, v.v[1] * f, v.v[2] * f);
}

vec3 operator*(const float f, const vec3& v) {
  return operator*(v, f);
}

vec3 operator/(const vec3& v, const float f) {
  return vec3(v.v[0] / f, v.v[1] / f, v.v[2] / f);
}

}

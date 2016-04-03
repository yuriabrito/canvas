#include <cmath>
#include "triangle_mesh.h"

namespace canvas {

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals,
    const std::vector<std::array<size_t, 3>>& faces) : vertices(vertices), normals(normals), faces(faces) {
}

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals,
    const std::vector<std::array<size_t, 3>>& faces, Material* material_ptr) :
  vertices(vertices), faces(faces), normals(normals), Hitable(material_ptr) {
}

bool TriangleMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  bool hit_anything = false;
  float closest_so_far = MAXFLOAT;
  hit_record rec_tmp;
  for(int i = 0; i < faces.size(); i++) {
    if(faceHit(i, r, 0.001, t_max, rec_tmp) && rec_tmp.t < closest_so_far) {
      hit_anything = true;
      closest_so_far = rec_tmp.t;
      rec = rec_tmp;
    }
  }
  return hit_anything;
}

// refactor t_min
bool TriangleMesh::faceHit(const int face_index,
    const ray& r, float t_min, float t_max, hit_record& rec) const {
  std::array<size_t, 3> face = faces[face_index];
  vec3 a, b, c;
  a = vertices[face[0]]; // v0
  b = vertices[face[1]]; // v1
  c = vertices[face[2]]; // v2

  vec3 e1, e2;
  e1 = b - a;
  e2 = c - a;

  vec3 P = r.d ^ e2;
  float det = e1 * P;
  if(det > -0.00001 && det < 0.00001) return false;

  float inv_det = 1.0 / det;

  vec3 T = r.o - a;

  float u = (T * P) * inv_det;
  if(u < 0.00001 || u > 1.0) return false;

  vec3 Q = T ^ e1;

  float v = (r.d * Q) * inv_det;
  if(v < 0.00001 || u + v > 1.0) return false;

  float t = (e2 * Q) * inv_det;

  if(t > t_min) {
    vec3 normal = (1-u-v) * normals[face[0]] + u * normals[face[1]] + v * normals[face[2]];
    rec.t = t;
    rec.p = r.point_at_parameter(t);
    rec.normal = normal;
    rec.material_ptr = material_ptr;
    return true;
  }

  return false;
}

}

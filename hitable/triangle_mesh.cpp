#include <cmath>
#include "triangle_mesh.h"

namespace canvas {

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices,
    const std::vector<std::array<unsigned int, 3>>& faces) : vertices(vertices), faces(faces) {
  flatTriangles();
}

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices,
    const std::vector<std::array<unsigned int, 3>>& faces,
    Material* material_ptr) :
  vertices(vertices), faces(faces), Hitable(material_ptr) {
    flatTriangles();
  }

bool TriangleMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  bool hit_anything = false;
  float closest_so_far = MAXFLOAT;
  hit_record rec_tmp;
  for(int i = 0; i < faces.size(); i++) {
    if(hitTriangle(i, r, 0.001, t_max, rec_tmp) && rec_tmp.t < closest_so_far) {
      hit_anything = true;
      closest_so_far = rec_tmp.t;
      rec = rec_tmp;
    }
  }
  return hit_anything;
}

// refactor t_min
bool TriangleMesh::hitTriangle(const int face_index,
    const ray& r, float t_min, float t_max, hit_record& rec) const {
  std::array<unsigned int, 3> face = faces[face_index];
  vec3 normal = normals[face_index];
  vec3 a, b, c;
  a = vertices[face[0]];
  b = vertices[face[1]];
  c = vertices[face[2]];

  vec3 e1, e2;
  e1 = b - a;
  e2 = c - a;

  vec3 P = r.d ^ e2;
  float det = e1 * P;
  if(det > -0.0001 && det < 0.0001) return false;

  float inv_det = 1.0 / det;

  vec3 T = r.o - a;

  float u = (T * P) * inv_det;
  if(u < 0.0 || u > 1.0) return false;

  vec3 Q = T ^ e1;

  float v = (r.d * Q) * inv_det;
  if(v < 0.0 || u + v > 1.0) return false;

  float t = (e2 * Q) * inv_det;

  if(t > t_min) {
    rec.t = t;
    rec.p = r.point_at_parameter(t);
    rec.normal = normal;
    rec.material_ptr = material_ptr;
    return true;
  }

  return false;
}

void TriangleMesh::smoothTriangles() {}

void TriangleMesh::flatTriangles() {
  for(int i = 0; i < faces.size(); i++) {
    normals.push_back((vertices[faces[i][0]] ^ vertices[faces[i][1]]).hat());
  }
}

}

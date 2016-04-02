#include <cmath>
#include "triangle_mesh.h"

namespace canvas {

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices,
    const std::vector<std::array<int, 3>>& faces) : vertices(vertices), faces(faces) {
  flatTriangles();
}

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices,
    const std::vector<std::array<int, 3>>& faces,
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
  std::array<int, 3> face = faces[face_index];
  vec3 normal = normals[face_index];

  vec3 a = vertices[face[0]];
  vec3 b = vertices[face[1]];
  vec3 c = vertices[face[2]];

  float t = normal * (a - r.o) / (normal * r.d);
  
  if(t < t_min || t > t_max) return false;

  vec3 p = r.point_at_parameter(t);

  vec3 ba = b - a; vec3 cb = c - b; vec3 ac = a - c;
  
  if(((ba ^ (p - a)) * normal) < 0.001 ||
      ((cb ^ (p - b)) * normal) < 0.001 ||
      ((ac ^ (p - c)) * normal) < 0.001) return false;

  rec.t = t;
  rec.p = p;
  rec.normal = normal;
  rec.material_ptr = material_ptr;
  return true;
}

void TriangleMesh::smoothTriangles() {}

void TriangleMesh::flatTriangles() {
  for(int i = 0; i < faces.size(); i++) {
    normals.push_back((vertices[faces[i][0]] ^ vertices[faces[i][1]]).hat());
  }
}

}

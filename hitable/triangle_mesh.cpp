#include <cmath>
#include "triangle_mesh.h"

namespace canvas {

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals,
    const std::vector<std::array<size_t, 3>>& faces) {
  for(const auto& f : faces) {
    Triangle* t = new Triangle(vertices[f[0]], vertices[f[1]], vertices[f[2]], normals[f[0]], normals[f[1]], normals[f[2]]);
    triangles.push_back(t);
  }
}

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals,
    const std::vector<std::array<size_t, 3>>& faces, Material* material_ptr)
  : TriangleMesh(vertices, normals, faces) {
    this->material_ptr = material_ptr;
}

bool TriangleMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  bool hit_anything = false;
  float closest_so_far = MAXFLOAT;
  hit_record rec_tmp;
  for(int i = 0; i < triangles.size(); i++) {
    if(triangles[i]->hit(r, 0.001, t_max, rec_tmp) && rec_tmp.t < closest_so_far) {
      hit_anything = true;
      closest_so_far = rec_tmp.t;
      rec = rec_tmp;
    }
  }
  if(hit_anything) rec.material_ptr = material_ptr;
  return hit_anything;
}

}

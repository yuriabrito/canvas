#include "triangle.h"
#include "triangle_mesh.h"

namespace canvas {

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals,
    const std::vector<std::array<size_t, 3>>& faces) {
  std::vector<Hitable*> triangles;
  for(const auto& f : faces) {
    Triangle* t = new Triangle(vertices[f[0]], vertices[f[1]], vertices[f[2]], normals[f[0]], normals[f[1]], normals[f[2]]);
    triangles.push_back(t);
  }
  kd_node = new KDNode();
  kd_node = kd_node->build(triangles, 0);
}

TriangleMesh::TriangleMesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals,
    const std::vector<std::array<size_t, 3>>& faces, Material* material_ptr)
  : TriangleMesh(vertices, normals, faces) {
    this->material_ptr = material_ptr;
}

bool TriangleMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  bool hit_anything = kd_node->hit(r, t_min, t_max, rec);
  if(hit_anything) rec.material_ptr = material_ptr;
  return hit_anything;
}

bool TriangleMesh::boundingBox(AABB& box) const {
  box = kd_node->box;
  return true;
}

}

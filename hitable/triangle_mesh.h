#ifndef HITABLE_TRIANGLEMESHH
#define HITABLE_TRIANGLEMESHH

#include <vector>
#include <array>
#include "util/vec3.h"
#include "hitable.h"

namespace canvas {

class TriangleMesh : public Hitable {
private:
  std::vector<vec3> vertices;
  std::vector<std::array<unsigned int, 3>> faces;
  std::vector<vec3> normals; // vertices
public:
  TriangleMesh(const std::vector<vec3>& vertices, const std::vector<vec3>& normals, const std::vector<std::array<unsigned int, 3>>& faces);
  TriangleMesh(const std::vector<vec3>& vertices, const std::vector<std::array<unsigned int, 3>>& faces, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  void smoothTriangles();
  void flatTriangles();
private:
  bool hitTriangle(const int face_index, const ray& r, float t_min, float t_max, hit_record& rec) const;
};

}

#endif

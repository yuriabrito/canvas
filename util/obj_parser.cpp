#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include "vec3.h"
#include "obj_parser.h"

namespace canvas {

TriangleMesh* ObjParser::parse(std::string file_path) {
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string err;
  bool ret = tinyobj::LoadObj(shapes, materials, err, file_path.c_str());

  if (!err.empty()) { // `err` may contain warning message.
    std::cerr << err << std::endl;
  }

  if (!ret) {
    exit(1);
  }

  int i = 0;

  size_t n_vertices = shapes[i].mesh.positions.size() / 3;
  size_t n_faces = shapes[i].mesh.indices.size() / 3;

  std::vector<vec3> vertices(n_vertices, vec3(0));
  std::vector<vec3> v_normals(n_vertices, vec3(0));
  //std::vector<vec3> f_normals(n_faces, vec3(0));
  //std::vector<std::vector<unsigned int>> v_f(n_vertices, {});
  std::vector<std::array<unsigned int, 3>> faces;

  for (size_t v = 0; v < n_vertices; v++) {
    vertices[v] = vec3(shapes[i].mesh.positions[3*v+0],
      shapes[i].mesh.positions[3*v+1],
      shapes[i].mesh.positions[3*v+2]);
  }

  for (size_t f = 0; f < n_faces; f++) {
    unsigned int v0, v1, v2;
    v0 = shapes[i].mesh.indices[3*f+0];
    v1 = shapes[i].mesh.indices[3*f+1];
    v2 = shapes[i].mesh.indices[3*f+2];
    //v_f[v0].push_back(f);
    //v_f[v1].push_back(f);
    //v_f[v2].push_back(f);
    // normal
    vec3 normal = vertices[v0] ^ vertices[v1];
    v_normals[v0] += normal;
    v_normals[v1] += normal;
    v_normals[v2] += normal;
    faces.push_back({v0, v1, v2});
  }

  for(size_t v = 0; v < n_vertices; v++) {
    v_normals[v].normalize();
  }

  return new TriangleMesh(vertices, v_normals, faces);
}

}

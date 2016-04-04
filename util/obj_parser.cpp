#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <vector>
#include <iostream>
#include "vec3.h"
#include "obj_parser.h"

namespace canvas {

void ObjParser::parse(const string& file_path, vector<vec3>& vertices,
    vector<vec3>& normals, vector<array<size_t, 3>>& faces) const {
  vector<tinyobj::shape_t> shapes;
  vector<tinyobj::material_t> materials;

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

  vector<size_t> v_degree(n_vertices, 0);
  vertices.resize(n_vertices);
  normals.resize(n_vertices);
  faces.reserve(n_faces);

  for(size_t v = 0; v < n_vertices; v++) {
    vertices[v] = vec3(shapes[i].mesh.positions[3*v+0],
      shapes[i].mesh.positions[3*v+1],
      shapes[i].mesh.positions[3*v+2]);
    normals[v] = vec3(0);
  }

  for(size_t f = 0; f < n_faces; f++) {
    unsigned int v0, v1, v2;
    v0 = shapes[i].mesh.indices[3*f+0];
    v1 = shapes[i].mesh.indices[3*f+1];
    v2 = shapes[i].mesh.indices[3*f+2];
    vec3 normal = (vertices[v1] - vertices[v0]) ^ (vertices[v2] - vertices[v0]);
    normals[v0] += normal;
    normals[v1] += normal;
    normals[v2] += normal;
    faces.push_back({v0, v1, v2});
  }

  for(size_t v = 0; v < n_vertices; v++) {
    normals[v].normalize();
  }
}

}

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

  std::vector<vec3> vertices;
  std::vector<std::array<unsigned int, 3>> faces;

  int i = 0;
  
  for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
    faces.push_back({shapes[i].mesh.indices[3*f+0],
        shapes[i].mesh.indices[3*f+1],
        shapes[i].mesh.indices[3*f+2]});
  }

  for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
    vertices.push_back(vec3(shapes[i].mesh.positions[3*v+0],
      shapes[i].mesh.positions[3*v+1],
      shapes[i].mesh.positions[3*v+2]));
  }

  return new TriangleMesh(vertices, faces);
}

}

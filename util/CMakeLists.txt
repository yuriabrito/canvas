project(util)

set(util_SRC
  tiny_obj_loader.cc tiny_obj_loader.h
  helpers.cpp helpers.h
  vec3.cpp vec3.h
  ray.cpp ray.h
  image.cpp image.h
  scene.cpp scene.h
  worker.cpp worker.h
  obj_parser.cpp obj_parser.h
  aabb.cpp aabb.h
  kd_node.cpp kd_node.h
  )

add_library(util ${util_SRC})

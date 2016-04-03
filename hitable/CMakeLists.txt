project(hitable)

set(hitable_SRC
  hitable.h
  hitable_list.cpp hitable_list.h
  sphere.cpp sphere.h
  triangle.cpp triangle.h
  triangle_mesh.cpp triangle_mesh.h
  )

add_library(hitable ${hitable_SRC})

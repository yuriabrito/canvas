project(hitable)

set(hitable_SRC
  hitable.h
  hitable_list.cpp hitable_list.h
  sphere.cpp sphere.h
  plane.cpp plane.h
  rectangle.cpp rectangle.h
  triangle.cpp triangle.h
  triangle_mesh.cpp triangle_mesh.h
  cube.cpp cube.h
  )

add_library(hitable ${hitable_SRC})

project(material)

set(material_SRC
  material.h
  lambertian.cpp lambertian.h
  metal.cpp metal.h
  )

add_library(material ${material_SRC})

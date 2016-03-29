project(material)

set(material_SRC
  material.h
  lambertian.cpp lambertian.h
  metal.cpp metal.h
  dielectric.cpp dielectric.h
  )

add_library(material ${material_SRC})

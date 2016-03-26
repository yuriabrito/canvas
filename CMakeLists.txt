cmake_minimum_required(VERSION 2.8)

project(canvas)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(.)

set(tests_SRC)
set(tests_LIBS)

FUNCTION(PREPEND var prefix)
  SET(listVar "")
  FOREACH(f ${ARGN})
    LIST(APPEND listVar "${prefix}/${f}")
  ENDFOREACH(f)
  SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

add_subdirectory(util)
add_subdirectory(tests)

message("${tests_SRC}")

add_executable(canvas main.cpp)

add_executable(canvas_tests tests/tests.cpp ${tests_SRC})
target_link_libraries(canvas_tests ${tests_LIBS})

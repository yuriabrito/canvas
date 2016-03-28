cmake_minimum_required(VERSION 2.8)

project(canvas)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(.)

set(tests_SRC)
set(tests_LIBS)

include(CMakeHelpers.txt)

add_subdirectory(util)
add_subdirectory(hitable)
add_subdirectory(camera)
add_subdirectory(tests)

add_executable(canvas main.cpp)
target_link_libraries(canvas util hitable camera)

add_executable(canvas_tests tests/tests.cpp ${tests_SRC})
target_link_libraries(canvas_tests ${tests_LIBS})

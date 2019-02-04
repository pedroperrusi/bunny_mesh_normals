cmake_minimum_required(VERSION 3.2)

# Enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(bunny_mesh_normals)
set(EXECUTABLE_OUTPUT_PATH "bin")

add_subdirectory(libs/cnpy)

add_executable(example src/example1.cpp)
target_link_libraries(example cnpy)
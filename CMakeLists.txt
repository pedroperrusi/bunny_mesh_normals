cmake_minimum_required(VERSION 3.2)

# Enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(bunny_mesh_normals)

set(EXECUTABLE_OUTPUT_PATH "bin")
# better intelisense in vscode editor
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (Eigen3 3.3 REQUIRED)

add_subdirectory(libs/cnpy)

add_executable(example src/main.cc)
target_link_libraries(example cnpy Eigen3::Eigen)
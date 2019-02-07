add_library(bunny_mesh "")

target_sources(
    bunny_mesh
    PRIVATE
        Mesh.cc
    PUBLIC
        ${CMAKE_HOME_DIRECTORY}/include/bunny_mesh/Mesh.h
        ${CMAKE_HOME_DIRECTORY}/include/bunny_mesh/data_io.h
    )

target_include_directories(
    bunny_mesh
    PUBLIC
        ${CMAKE_HOME_DIRECTORY}/include
    )


find_package (Eigen3 3.3 REQUIRED)

target_link_libraries(bunny_mesh cnpy Eigen3::Eigen)

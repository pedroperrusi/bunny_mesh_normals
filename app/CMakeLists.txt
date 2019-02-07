add_executable(
    bunny_mesh_normals
    main.cc
    )

find_package (Eigen3 3.3 REQUIRED)

target_include_directories(
    bunny_mesh_normals
    PUBLIC
        ${CMAKE_HOME_DIRECTORY}/include
    )

target_link_libraries(bunny_mesh_normals bunny_mesh)

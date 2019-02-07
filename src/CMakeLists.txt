add_executable(
    bunny_mesh_normals
    main.cc
    Mesh.cc
    )

find_package (Eigen3 3.3 REQUIRED)

target_link_libraries(bunny_mesh_normals cnpy Eigen3::Eigen)

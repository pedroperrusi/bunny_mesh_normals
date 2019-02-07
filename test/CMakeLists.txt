add_executable(
    bunny_tests
    test_Mesh.cc
    test_IO.cc
  )

target_link_libraries(
    bunny_tests
    bunny_mesh
    gtest_main
  )

target_include_directories(
    bunny_tests
    PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include
  )

add_test(
    NAME
      unit
    COMMAND
      ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )

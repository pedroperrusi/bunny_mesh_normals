cmake_minimum_required(VERSION 3.2)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)

project(bunny-mesh)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# better intelisense in vscode editor
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add cnpy library subdirectory
add_subdirectory(extern/cnpy)

# add project source code subdirectory
add_subdirectory(src)
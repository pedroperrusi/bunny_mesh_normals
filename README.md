<!-- File written based on GitHub markdown -->
# Bunny Mesh Normals

Ladies and gentlemen, I would like to introduce you the famous [Stanford Bunny][wiki_bunny] Triangle Mesh. If you would like to get to know him better, Georgia Tech provides an [overview][bunny_story] of his history and Stanford shares [his data source][Stanford_Source] and many other 3D models.

<!-- References -->
[wiki_bunny]: https://en.wikipedia.org/wiki/Stanford_bunny
[bunny_story]: https://www.cc.gatech.edu/~turk/bunny/bunny.html
[Stanford_Source]: http://graphics.stanford.edu/data/3Dscanrep/

## The Challenge

Given the mesh data of the Stanford bunny, saved in the numpy format, the challenge is to develop a C++ program that computes:

1 - Normalized normals at each face of the object;

2 - Normalized normals at each vertex of the object.

### Dependencies

* [ZLIB](https://www.zlib.net)

* [Eigen](http://eigen.tuxfamily.org/)

* [CMake](https://cmake.org)

### External Libraries

* CNPY: IO operations between numpy files and C/C++ data structures.

* Google Tests (Gtest): Basic testing functionalities. The CMake and Gtest integration was based on the [gtest-demo](https://github.com/bast/gtest-demo) repository.

### Usage

In order to perform the basic interface with the bunny-mesh project, you may use the helping bash scripts of the folder [scripts](scripts/). Their names are mostly self explanatory.

In order to generate the CMake files:

```(bash)
bash scripts/cmake.sh
```

In order to build and compile:

```(bash)
bash scripts/build.sh
```

Finally you may run the project:

```(bash)
bash scripts/run_bunny_mesh_normals.sh
```

* Other commands:

To remove the build folder:

```(bash)
bash scripts/clean.sh
```

To run unit tests:

```(bash)
bash scripts/run_tests.sh
```

## References

Information sources that were quite useful to understand and perform the triagular mesh operations:

* https://en.wikipedia.org/wiki/Polygon_mesh
* https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-normals
* http://www.iquilezles.org/www/articles/normals/normals.htm

## Project Structure

The project structure is based on [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/).
Some adjustments would also be interesting, such as downloading the external dependency CNPY from a CMake file.

```
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── app
│   ├── CMakeLists.txt
│   └── main.cc
├── cmake
│   ├── googletest-download.cmake
│   └── googletest.cmake
├── data
│   ├── bunny_faces.npy
│   ├── bunny_vertices.npy
│   ├── face_normals.npy
│   └── vertex_normals.npy
├── extern
│   └── cnpy
│       ├── CMakeLists.txt
│       ├── LICENSE
│       ├── README.md
│       ├── cnpy.cpp
│       ├── cnpy.h
│       ├── example1.cpp
│       ├── mat2npz
│       ├── npy2mat
│       └── npz2mat
├── include
│   └── bunny_mesh
│       ├── Mesh.h
│       └── data_io.h
├── python
│   └── visualize_mesh.py
├── scripts
│   ├── build.sh
│   ├── clean.sh
│   ├── cmake.sh
│   ├── run_bunny_mesh_normals.sh
│   └── run_tests.sh
├── src
│   ├── CMakeLists.txt
│   └── Mesh.cc
└── test
    ├── CMakeLists.txt
    ├── data
    │   ├── sequential_double.npy
    │   └── sequential_int.npy
    ├── test_IO.cc
    └── test_Mesh.cc
```
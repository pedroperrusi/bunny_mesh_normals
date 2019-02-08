<!-- File written based on GitHub markdown -->
# Bunny Mesh Normals

Ladies and gentlemen, I would like to introduce you the famous [Stanford Bunny][wiki_bunny] Triangle Mesh. If you would like to get to know him better, Georgia Tech provides an [overview][bunny_story] of his history and Stanford shares [his data source][Stanford_Source] and many other 3D models.

## The Challenge

Given the mesh data of the Stanford bunny, saved in the numpy format, the challenge is to develop a C++ program that computes:

1 - Normalized normals at each face of the object;

2 - Normalized normals at each vertex of the object.

## Dependencies

* [ZLIB](https://www.zlib.net)

* [Eigen](http://eigen.tuxfamily.org/)

* [CMake](https://cmake.org)

## External Libraries

* CNPY: IO operations between numpy files and C/C++ data structures.

* Google Tests (Gtest): Basic testing functionalities. The CMake and Gtest integration was based on the [gtest-demo](https://github.com/bast/gtest-demo) repository.

## Usage

In order to perform the basic interface with the bunny-mesh project, you may use the helping bash scripts of the folder [scripts](scripts/). Their names are mostly self explanatory.

* 1: Build

In order to build the CMake project:

```(bash)
bash scripts/build.sh
```

* 2: Compile

Just after building:

```(bash)
bash scripts/compile.sh
```

* 3: Run Project

Finaly:

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

<!-- References -->
[wiki_bunny]: https://en.wikipedia.org/wiki/Stanford_bunny
[bunny_story]: https://www.cc.gatech.edu/~turk/bunny/bunny.html
[Stanford_Source]: http://graphics.stanford.edu/data/3Dscanrep/
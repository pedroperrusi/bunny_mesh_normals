#!/bin/bash

echo 'Compiling Bunny Mesh Project...'

# create build directory if it doesn't exist
mkdir -p build 
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=build/
make
make install

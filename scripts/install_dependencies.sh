#!/bin/bash

echo 'Installing cnpy module...'

cd libs/cnpy
# create build directory if it doesnt exist
mkdir -p build 
cd build
cmake ../
make
make install

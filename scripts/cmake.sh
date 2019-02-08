#!/bin/bash

echo 'Building Bunny Mesh Project...'

# create build directory if it doesn't exist
mkdir -p build 
cd build
cmake ../ 
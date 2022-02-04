#!/bin/bash

echo "Current directory: $(pwd)"
rm -rf ./build
mkdir build
echo "Build directory recreated"

cmake_keys="-DTESTING=ON"
cd ./build || (echo "Directory was not created" && exit 127)
echo "Start cmake scenario keys $cmake_keys"
cmake $cmake_keys ..

echo "REBUILD FINISHED!"
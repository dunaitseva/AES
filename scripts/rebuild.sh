#!/bin/bash

BUILD_DIR="./build"
LOG_FILE="./tmp/build.log"
TMP_DIR="./tmp"

rm -rf $BUILD_DIR
mkdir -p $TMP_DIR
touch $LOG_FILE
mkdir $BUILD_DIR && echo "Creating $BUILD_DIR directory"

CMAKE_KEYS="-DTESTING=ON"
echo "CMakeFile.txt will execute with $CMAKE_KEYS options"

echo "Executing CMakeFile.txt"
cmake $CMAKE_KEYS -B $BUILD_DIR -S . >> $LOG_FILE || (echo "Error, check $LOG_FILE")

echo "Build targets with make"
make --directory=$BUILD_DIR >> $LOG_FILE || (echo "Error, check $LOG_FILE")

echo "REBUILD FINISHED!"
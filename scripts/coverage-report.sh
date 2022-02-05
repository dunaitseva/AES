#!/bin/bash

BUILD_DIRECTORY="build"

pip install gcovr

./scripts/rebuild.sh -c -t

cd $BUILD_DIRECTORY || (echo "Error. $BUILD_DIRECTORY not created." && exit 1)
ctest
cd ..
EXCLUDING_FILES=".*_deps.*|.*tests.*"
REPORT_FILE_NAME="coverage.xml"
gcovr -r . ./build -e $EXCLUDING_FILES -o $REPORT_FILE_NAME --xml
#gcovr -r . ./build -e $EXCLUDING_FILES -o cov.html --html
#gcovr -r . ./build -e $EXCLUDING_FILES

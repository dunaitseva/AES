#!/bin/bash

pathStateTests="./build/CMakeFiles/StateTests.dir/tests/StateTests.cpp"
pathBaseCryptoUtilsTests="./build/CMakeFiles/BaseCryptoUtilsTests.dir/tests/BaseCryptoUtilsTests.cpp"
pathRijndaelTests="./build/CMakeFiles/RijndaelTests.dir/tests/RijndaelTests.cpp"
pathKeyScheduleTests="./build/CMakeFiles/KeyScheduleTests.dir/tests/KeyScheduleTests.cpp"

mkdir cov

cp $pathStateTests.gcda ./cov/StateTests.cpp.gcda
cp $pathStateTests.gcda ./cov/BaseCryptoUtilsTests.cpp.gcda
cp $pathStateTests.gcda ./cov/RijndaelTests.cpp.gcda
cp $pathStateTests.gcda ./cov/KeyScheduleTests.cpp.gcda

cp $pathStateTests.gcno ./cov/StateTests.cpp.gcno
cp $pathStateTests.gcno ./cov/BaseCryptoUtilsTests.cpp.gcno
cp $pathStateTests.gcno ./cov/RijndaelTests.cpp.gcno
cp $pathStateTests.gcno ./cov/KeyScheduleTests.cpp.gcno

cd cov
lcov -t "Test Coverage" --capture --external -o test-coverage.info -c -d .
#genhtml test-coverage.info --branch-coverage --output-directory ./code_coverage_report/

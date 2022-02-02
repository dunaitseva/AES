#!/bin/bash

pathStateTests="./build/CMakeFiles/StateTests.dir/tests/StateTests.cpp"
pathBaseCryptoUtilsTests="./build/CMakeFiles/BaseCryptoUtilsTests.dir/tests/BaseCryptoUtilsTests.cpp"
pathRijndaelTests="./build/CMakeFiles/RijndaelTests.dir/tests/RijndaelTests.cpp"
pathKeyScheduleTests="./build/CMakeFiles/KeyScheduleTests.dir/tests/KeyScheduleTests.cpp"

rm -rf cov
mkdir cov

cp $pathStateTests.gcda ./cov/StateTests.cpp.gcda
cp $pathBaseCryptoUtilsTests.gcda ./cov/BaseCryptoUtilsTests.cpp.gcda
cp $pathRijndaelTests.gcda ./cov/RijndaelTests.cpp.gcda
cp $pathKeyScheduleTests.gcda ./cov/KeyScheduleTests.cpp.gcda

cp $pathStateTests.gcno ./cov/StateTests.cpp.gcno
cp $pathBaseCryptoUtilsTests.gcno ./cov/BaseCryptoUtilsTests.cpp.gcno
cp $pathRijndaelTests.gcno ./cov/RijndaelTests.cpp.gcno
cp $pathKeyScheduleTests.gcno ./cov/KeyScheduleTests.cpp.gcno

cd cov
lcov -t "Test Coverage" -o test-coverage.info -c -d .
lcov --list test-coverage.info
#genhtml test-coverage.info --branch-coverage --output-directory ./code_coverage_report/

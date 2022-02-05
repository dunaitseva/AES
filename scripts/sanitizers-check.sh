#!/bin/bash

BUILD_DIR="./build"

./scripts/rebuild.sh -s -t

./build/StateTests
./build/RijndaelTests
./build/KeyScheduleTests
./build/BaseCryptoUtilsTests
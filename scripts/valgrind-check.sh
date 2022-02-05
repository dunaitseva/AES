#!/bin/bash

BUILD_DIR="build"

./scripts/rebuild.sh

# Тут нужно будет дописать диагностические сообщения
valgrind --tool=memcheck ./$BUILD_DIR/StateTests > /dev/null
valgrind --tool=memcheck ./$BUILD_DIR/BaseCryptoUtilsTests > /dev/null
valgrind --tool=memcheck ./$BUILD_DIR/KeyScheduleTests > /dev/null
valgrind --tool=memcheck ./$BUILD_DIR/RijndaelTests > /dev/null

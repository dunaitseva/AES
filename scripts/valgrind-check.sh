#!/bin/bash

sudo apt install valgrind > /dev/null && echo "valgrind is already installed" || echo "Error while installing valgrind"

BUILD_DIR="./build"
VALGRIND_LOG_FILE="./tmp/valgrind-check.log"
TMP_DIR="./tmp"

mkdir -p $TMP_DIR
touch $VALGRIND_LOG_FILE

./scripts/rebuild.sh

diagnostic_message () {
  echo "Error, $1 valgrind check. Check log file $VALGRIND_LOG_FILE."
}

VALGRIND_OPTIONS="--tool=memcheck --leak-check=full --track-origins=yes -s --log-file=$VALGRIND_LOG_FILE"

# Тут нужно будет дописать диагностические сообщения
#valgrind --tool=memcheck ./$BUILD_DIR/StateTests > $VALGRIND_LOG_FILE || (diagnostic_message "StateTests" && exit 1)
#valgrind --tool=memcheck ./$BUILD_DIR/BaseCryptoUtilsTests > $VALGRIND_LOG_FILE || (diagnostic_message "BaseCryptoUtilsTests" && exit 1)
#valgrind --tool=memcheck ./$BUILD_DIR/KeyScheduleTests > $VALGRIND_LOG_FILE || (diagnostic_message "KeyScheduleTests" && exit 1)
#valgrind --tool=memcheck ./$BUILD_DIR/RijndaelTests > $VALGRIND_LOG_FILE || (diagnostic_message "RijndaelTests" && exit 1)
echo "-----> START StateTests CHECK"
valgrind $VALGRIND_OPTIONS ./$BUILD_DIR/StateTests >> /dev/null || (diagnostic_message "StateTests" && exit 1)

echo "-----> START BaseCryptoUtilsTests CHECK"
valgrind $VALGRIND_OPTIONS ./$BUILD_DIR/BaseCryptoUtilsTests >> /dev/null || (diagnostic_message "BaseCryptoUtilsTests" && exit 1)

echo "-----> START KeyScheduleTests CHECK"
valgrind $VALGRIND_OPTIONS ./$BUILD_DIR/KeyScheduleTests >> /dev/null || (diagnostic_message "KeyScheduleTests" && exit 1)

echo "-----> START RijndaelTests CHECK"
valgrind $VALGRIND_OPTIONS ./$BUILD_DIR/RijndaelTests >> /dev/null || (diagnostic_message "RijndaelTests" && exit 1)
cmake_minimum_required(VERSION 3.16)
project(AES)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wpedantic -Wextra")

set(PROJECT_SOURCE_DIR project/src)
set(PROJECT_INCLUDE_DIR project/include)

add_library(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/Rijndael.cpp
        ${PROJECT_SOURCE_DIR}/State.cpp
        ${PROJECT_SOURCE_DIR}/KeySchedule.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})
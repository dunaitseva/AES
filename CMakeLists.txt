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

option(TESTING "If this flag is enabled, CMake build tests" OFF)
if (${TESTING})
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

#add_executable(
#        hello_test
#        tests/test.cpp
#)
#
#target_link_libraries(
#        hello_test
#        gtest_main
#)

include(GoogleTest)
gtest_discover_tests(hello_test)
endif()
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
        ${PROJECT_SOURCE_DIR}/BaseCryptoUtils.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})

option(TESTING "If this flag is enabled, CMake build tests" OFF)
if (${TESTING})
    target_compile_options(${PROJECT_NAME} PUBLIC "--coverage")
    target_link_libraries(${PROJECT_NAME} PUBLIC gcov)

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(CTEST_SOURCE_DIRECTORY tests)

    FetchContent_MakeAvailable(googletest)

    enable_testing()

    set(STATE StateTests)
    set(KEY_SCHEDULE KeyScheduleTests)
    set(RIJNDAEL RijndaelTests)
    set(BASE_CRYPTO_UTILS BaseCryptoUtilsTests)

    add_executable(${STATE} ${CTEST_SOURCE_DIRECTORY}/${STATE}.cpp)
    target_link_libraries(${STATE} gtest_main)
    target_link_libraries(${STATE} ${PROJECT_NAME})

    add_executable(${KEY_SCHEDULE} ${CTEST_SOURCE_DIRECTORY}/${KEY_SCHEDULE}.cpp)
    target_link_libraries(${KEY_SCHEDULE} gtest_main)
    target_link_libraries(${KEY_SCHEDULE} ${PROJECT_NAME})

    add_executable(${RIJNDAEL} ${CTEST_SOURCE_DIRECTORY}/${RIJNDAEL}.cpp)
    target_link_libraries(${RIJNDAEL} gtest_main)
    target_link_libraries(${RIJNDAEL} ${PROJECT_NAME})

    add_executable(${BASE_CRYPTO_UTILS} ${CTEST_SOURCE_DIRECTORY}/${BASE_CRYPTO_UTILS}.cpp)
    target_link_libraries(${BASE_CRYPTO_UTILS} gtest_main)
    target_link_libraries(${BASE_CRYPTO_UTILS} ${PROJECT_NAME})

    include(GoogleTest)

    gtest_discover_tests(${STATE})
    gtest_discover_tests(${KEY_SCHEDULE})
    gtest_discover_tests(${RIJNDAEL})
    gtest_discover_tests(${BASE_CRYPTO_UTILS})

endif ()
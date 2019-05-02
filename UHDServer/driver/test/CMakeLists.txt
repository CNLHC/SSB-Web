cmake_minimum_required(VERSION 3.5)

project(googletest)

include(CTest)
enable_testing()


find_package(GTest REQUIRED)


add_executable(runUnitTests testUM2xx.cpp
        ../source/src/UM2xx.cpp
        )

include_directories(${GTEST_INCLUDE_DIRS}
        ../source/inc
        )

target_link_libraries(runUnitTests
        ${GTEST_BOTH_LIBRARIES}
        pthread
        ${serial_LIBRARIES}
        )

add_test(AllTests runUnitTests)


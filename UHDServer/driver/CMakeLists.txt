cmake_minimum_required(VERSION 3.3)

project(UM2xxDriver)
set(serial_DIR  /usr/local/share/serial/cmake/)
FIND_PACKAGE(serial REQUIRED)
include_directories( ${serial_INCLUDE_DIRS})


add_subdirectory(source)
add_subdirectory(test)

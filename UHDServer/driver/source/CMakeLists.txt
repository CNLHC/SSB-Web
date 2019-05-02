cmake_minimum_required(VERSION 3.12)
project(UM2xxDriver)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)


add_executable(UM2xxDriver
        main.cpp
        src/UM2xx.cpp
        inc/UM2xx.h
        inc/UM2xxOpCode.h
        src/UM2xxCMD.cpp
        inc/mqttclient.hpp
        )

target_link_libraries(UM2xxDriver
        ${serial_LIBRARIES}
        ${PAHO_MQTT_C_LIBRARIES}
        libpaho-mqttpp3.so

        )


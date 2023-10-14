cmake_minimum_required(VERSION 3.0)
project(waybar-bluetooth_battery_parse)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(SOURCE_FILES 
    src/waybar-bluetooth_battery_parse.c
)

include_directories(include)

add_executable(waybar-bluetooth_battery_parse ${SOURCE_FILES})

install(TARGETS waybar-bluetooth_battery_parse)

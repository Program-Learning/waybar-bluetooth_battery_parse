cmake_minimum_required(VERSION 3.0)
project(waybar-bluetooth_battery_parse C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(include)

file(GLOB SOURCE_FILES "src/*.c")

add_executable(waybar-bluetooth_battery_parse ${SOURCE_FILES})

install(TARGETS waybar-bluetooth_battery_parse)

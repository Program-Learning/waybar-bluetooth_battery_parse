cmake_minimum_required(VERSION 3.10.2)
project(waybar-bluetooth_battery_parse C)

AUX_SOURCE_DIRECTORY(./src DIR_SRC)
add_executable(waybar-bluetooth_battery_parse ${DIR_SRC})

target_include_directories(waybar-bluetooth_battery_parse PUBLIC include)

install(TARGETS waybar-bluetooth_battery_parse DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)